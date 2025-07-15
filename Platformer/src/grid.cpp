//Libraries
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

//Standard Libraries
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

//Header Files
#include "Levels.hpp"
#include "grid.hpp"

/*
TODO: Make a vector of Textures & refactor some code
*/

//Initialzing Global Variables
Grid::Grid(){

    numRows = 34;
    NumCols = 60;
    cellSize = 32;
    //Put all textures here
    Textures = {LoadTexture("Graphics/MetalThing.png"), LoadTexture("Graphics/Grass(?).png"), LoadTexture("Graphics/Grater.png"), 
    LoadTexture("Graphics/Chain.png"), LoadTexture("Graphics/Pipe.png"), LoadTexture("Graphics/Pipe2.png"), LoadTexture("Graphics/Latern.png")};
    index = 0;
    //Gets all of the level paths from Levels.cpp & Levels.hpp
    Levels = returnbingus();
    //Completely Arbitrary
    TileSelected = 0;

}

//This function auto-generates walls at the given position
void Grid::MakeWalls(int column, int row){
    
    //Floor (Top part of the tile, the one that the player stands on)
    FloorCollisionBoxes.push_back(Rectangle{static_cast<float>(column * cellSize + 1), 
    static_cast<float>(row * cellSize + 1), cellSize, 16});
    
    //Left Side
    LeftCollisionBoxes.push_back(Rectangle{static_cast<float>(column * cellSize + 1), 
        static_cast<float>(row * cellSize + 1), 8, cellSize - 2});
    
    //Right Side
    RightCollisionBoxes.push_back(Rectangle{static_cast<float>((column * cellSize) + cellSize - 7),
        static_cast<float>(row * cellSize + 1), 8, cellSize - 2});

    //Bottom Side
    BottomCollisionBoxes.push_back(Rectangle{static_cast<float>(column * cellSize + 6),
        static_cast<float>((row * cellSize) + cellSize), cellSize - 8, 8});

}   

//Intializes/Regenerates the level
void Grid::Initialize(){
    
    //Read from the given index of levels (i.e the level we want)
    std::ifstream ReadFile(Levels[index]);
    
    //(See Grid::Update() notes)
    OldLevel = Levels[index];
    std::string line;
    int row = 0;

    //Clears the old collisions
    FloorCollisionBoxes.clear();
    LeftCollisionBoxes.clear();
    RightCollisionBoxes.clear();
    BottomCollisionBoxes.clear();

    //Reads the given level (.txt) file line by line incrementing column & row as needed
    while(std::getline(ReadFile, line) && row < numRows) {
        
        for(int column = 0; column < NumCols; column++) {
            
            grid[row][column] = line[column] - '0';
            if(grid[row][column] != 0 && grid[row][column] != 4){MakeWalls(column, row);}

        }    
    
        row++;
    }
    
    //Closes the file
    ReadFile.close();

}

//Actually drawing the textures at the given locations
void Grid::Draw(){

    //Increments row & column
    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            DrawTexture(Textures[grid[row][column] - 1], column * cellSize + 1, row * cellSize + 1, WHITE);
        
        }   
    
    }

    int snappedX = std::round((GetMouseX() - cellSize / 2) / (float)cellSize) * cellSize + 1;
    int snappedY = std::round((GetMouseY() - cellSize / 2) / (float)cellSize) * cellSize + 1;

    //Draws the Currently Selected Tile from the Tile Editor
    DrawTexture(Textures[TileSelected - 1], snappedX, snappedY, WHITE);

}   

void Grid::Update(){

    //DEBUG
    if(IsKeyPressed(KEY_SPACE)){

        index = index + 1;
        
        if(index > 1){

            index = 0;

        }

    }
    /*If the level the player is SUPPOSED to be at != the one they ARE at than we 
    re-initialize the grid, this time with the new level path the player is SUPPOSED to be at
    OldLevel is than regenerated and the cycle repeats */
    
    if(Levels[index] != OldLevel){Initialize();}
    
    //The Tile Placing Code (This took so goddman long)
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false){

        //Creates a Read Only instance of the current level
        std::ifstream ReadFile(Levels[index]);
        
        //Two strings, one which holds the current line string and the other which holds the full file 
        std::string ContentsInCurrentLine;
        std::string FullFile;
        
        //Copies everything in the file from a string
        while(std::getline(ReadFile, ContentsInCurrentLine)){

            FullFile.append(ContentsInCurrentLine + "\n");

        }

        //Converts 2D coordinates into 1D (The (NumCols + 2) skips over the \n's) and then changes the letter accordingly 
        //TileSelected + '0' converts the current value of TileSelected to characters and then adds them to the file
        FullFile[std::round((GetMouseY() - cellSize / 2) / cellSize) * (NumCols + 2) + std::round((GetMouseX() - cellSize / 2) / cellSize)] 
        = TileSelected + '0';
        
        //Closes the read only instance
        ReadFile.close();

        //Opens a write-only instance (This had to be done because WriteFile << FullFile didn't work with just std::fstream)
        std::ofstream WriteFile(Levels[index]);

        WriteFile << FullFile;
        WriteFile.close();
        //Re-intializes the level with the new values
        Initialize();

    }   

}

//Renders and Intializes the Level Editor UI
void Grid::RenderUI(){

    ImGui::Begin("Level Editor/Tile Selector");

    //Sets the current Counter to 0
    int Counter = 0;
    //Sets the default name to Metal
    std::string Name = "Metal";
    static int selectedIdx = -1;

    for (int y = 0; y < 3; ++y) {
        
        for (int x = 0; x < 3; ++x) {
            
            //This is basically unnecessary but it helps for code readability
            int idx = Counter;
            if (x > 0) ImGui::SameLine();
            ImGui::PushID(idx);

            //Makes sure only one thing is selected (If idx == selected is true than isSelected will be true & Vice Versa)
            bool isSelected = (idx == selectedIdx);
            if(ImGui::Selectable(Name.c_str(), &isSelected, 0, ImVec2(64, 64))) {
                
                selectedIdx = idx;
                //We pass TileSelected to the Draw() function so we can draw the tile
                TileSelected = idx + 1;
                
                if(TileSelected > 7){TileSelected = 0;}

            }
            
            //This is all for drawing the STUPID F*CKING TEXTURE
            ImVec2 min = ImGui::GetItemRectMin();
            ImVec2 max = ImGui::GetItemRectMax();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 center = ImVec2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);
            ImVec2 img_min = ImVec2(center.x - 16, center.y - 16);
            ImVec2 img_max = ImVec2(center.x + 16, center.y + 16);
            
            //Naming and Drawing the Preview on the Level Editor window
            if(Counter == 0){

                //Because of the way this is formated the name of the NEXT item is declared
                Name = "Dotted"; 
            
            }
            else if(Counter == 1){Name = "Grater";}
            else if(Counter == 2){Name = "Chain";}
            else if(Counter == 3){Name = "Pipe2";}
            else if(Counter == 4){Name = "Pipe";}
            else if(Counter == 5){Name = "Latern";}
            else if(Counter == 6){Name = "Default";}
            else{draw_list->AddImage((ImTextureID)Textures[0].id, img_min, img_max);}
            if(Counter < 7){draw_list->AddImage((ImTextureID)Textures[Counter].id, img_min, img_max);}

            //Increments the Counter
            Counter++;

            ImGui::PopID();

        }
    
    }

    ImGui::End();

}
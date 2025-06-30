#include "grid.hpp"
#include<iostream>
#include "raylib.h"
#include<fstream>
#include<string>
#include "Levels.hpp"

//Initialzing Global Variables
Grid::Grid(){

    numRows = 34;
    NumCols = 60;
    cellSize = 32;
    //Put all textures here
    MetalThing = LoadTexture("Graphics/MetalThing.png");
    Grass = LoadTexture("Graphics/Grass(?).png");
    Grater = LoadTexture("Graphics/Grater.png");
    Chain = LoadTexture("Graphics/Chain.png");
    Pipe = LoadTexture("Graphics/Pipe.png");
    Pipe2 = LoadTexture("Graphics/Pipe2.png");
    index = 0;
    //Gets all of the level paths from Levels.cpp & Levels.hpp
    Levels = returnbingus();

}

//This function auto-generates walls at the given position
void Grid::MakeWalls(int column, int row){
    
    //Floor (Top part of the tile, the one that the player stands on)
    FloorCollisionBoxes.push_back(Rectangle{static_cast<float>(column * cellSize + 1), 
    static_cast<float>(row * cellSize + 1), cellSize, 8});
    
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
    while (std::getline(ReadFile, line) && row < numRows) {
        
        for (int column = 0; column < NumCols; column++) {
            
            //If '0' set that space in grid to also equal zero (See Grid::Draw)
            if (line[column] == '0') {
                
                grid[row][column] = 0;
            
            } 
            
            //Same thing but if the given tile equals 1
            else if (line[column] == '1') {
                
                grid[row][column] = 1;
                MakeWalls(column, row);

            } 
            
            else if(line[column] == '2'){

                grid[row][column] = 2;
                MakeWalls(column, row);

            }

            else if(line[column] == '3'){

                grid[row][column] = 3;
                MakeWalls(column, row);

            }

            else if(line[column] == '4'){

                grid[row][column] = 4;
                MakeWalls(column, row);

            }

            else if(line[column] == '5'){

                grid[row][column] = 5;
                MakeWalls(column, row);

            }

            else if(line[column] == '6'){

                grid[row][column] = 6;
                MakeWalls(column, row);

            }

            //Failsafe (TODO: Put a "missing" texture here)
            else {
                
                grid[row][column] = 0;
            
            }
        
        }    
        
        row++;
    }
    
    //Closes the file
    ReadFile.close();

}

//Just for debugging, simply runs through grid[][] and prints all the values
void Grid::Print(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            std::cout << grid[row][column];

        }

        std::cout << std::endl;

    }

}

//Actually drawing the textures at the given locations
void Grid::Draw(){

    //Increments row & column
    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            //If grid[row][column] equals 1 then print the MetalThing texture with the given size
            if(grid[row][column] == 1){

                DrawTexture(MetalThing, column * cellSize + 1, row * cellSize + 1, WHITE);
                
            }   
            
            //Grass Texture (Actually the tile with 4 dots)
            else if(grid[row][column] == 2){

                DrawTexture(Grass, column * cellSize + 1, row * cellSize + 1, WHITE);

            }
            
            //Grater/Cage texture
            else if(grid[row][column] == 3){

                DrawTexture(Grater, column * cellSize + 1, row * cellSize + 1, WHITE);

            }

            //Chain texture
            else if(grid[row][column] == 4){

                DrawTexture(Chain, column * cellSize + 1, row * cellSize + 1, WHITE);

            }

            //Pipe (The less fun version)
            else if(grid[row][column] == 5){

                DrawTexture(Pipe2, column * cellSize + 1, row * cellSize + 1, WHITE);

            }

            //Pipe (More Fun Version)
            else if(grid[row][column] == 6){

                DrawTexture(Pipe, column * cellSize + 1, row * cellSize + 1, WHITE);

            }

        }   
    
    }

}

void Grid::Update(){

    //DEBUG
    if(IsKeyPressed(KEY_SPACE)){

        index = index + 1;
        
        if(index > 1){

            index = 0;

        }

    }
    /*
    If the level the player is SUPPOSED to be at != the one they ARE at than we 
    re-initialize the grid, this time with the new level path the player is SUPPOSED to be at
    OldLevel is than regenerated and the cycle repeats
    */
    if(Levels[index] != OldLevel){

        Initialize();

    }

}

#include "grid.hpp"
#include<iostream>
#include "raylib.h"
#include<fstream>
#include<string>
#include "Levels.hpp"

//Initialzing Global Variables
Grid::Grid(){

    //For expandability (although the values of grid[][] are hardcoded)
    numRows = GetScreenHeight() / 32;
    NumCols = GetScreenWidth() / 32;
    //33 or 32, haven't decided
    cellSize = 33;
    //Put all textures here
    MetalThing = LoadTexture("Graphics/MetalThing.png");
    index = 0;
    //Gets all of the level paths from Levels.cpp & Levels.hpp
    Levels = returnbingus();

}

//Intializes/Regenerates the level
void Grid::Initialize(){
    
    //Read from the given index of levels (i.e the level we want)
    std::ifstream ReadFile(Levels[index]);
    
    //(See Grid::Update() notes)
    OldLevel = Levels[index];
    std::string line;
    int row = 0;
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

//Just for debuging, simply runs through grid[][] and prints all the values
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

            //If grid[row][column] equals 1 than print the MetalThing texture with the given size
            if(grid[row][column] == 1){

                DrawTexture(MetalThing, column * cellSize + 1, row * cellSize + 1, WHITE);

            }
            
            if(grid[row][column] != 0){

                //Big ol' thang (I'm going f*cking insane)
                CollisionBoxes.push_back(Rectangle{static_cast<float>(column * cellSize + 1), 
                static_cast<float>(row * cellSize + 1), cellSize + 1, cellSize + 1});

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
    If the level the player is SUPPOSED to be at =! the one they ARE at than we 
    re-initialize the grid, this time with the new level path the player is SUPPOSED to be at
    OldLevel is than regenerated and the cycle repeats
    */
    if(Levels[index] != OldLevel){

        Initialize();

    }

}
#include "grid.hpp"
#include<iostream>
#include "raylib.h"
#include<fstream>
#include<string>
#include "Levels.hpp"

Grid::Grid(){

    numRows = GetScreenHeight() / 32;
    NumCols = GetScreenWidth() / 32;
    //33 or 32, haven't decided
    cellSize = 33;
    Texture = LoadTexture("Graphics/MetalThing.png");
    index = 0;

}

void Grid::Initialize(){
    
    Levels = returnbingus();
    std::ifstream ReadFile(Levels[index]);

    std::string line;
    int row = 0;
    while (std::getline(ReadFile, line) && row < numRows) {
        
        for (int column = 0; column < NumCols; column++) {
            
            if (line[column] == '0') {
                
                grid[row][column] = 0;
            
            } 
            
            else if (line[column] == '1') {
                
                grid[row][column] = 1;
            
            } 
            
            else {
                
                grid[row][column] = 0;
            
            }
        }    
        
        row++;
    }
    
    ReadFile.close();

    //DEBUG
    if(IsKeyPressed(KEY_SPACE)){

        index = index + 1;

        if(index > 1){

            index = 0;

        }

    }

}

void Grid::Print(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            std::cout << grid[row][column];

        }

        std::cout << std::endl;

    }

}

void Grid::Draw(){

    for(int row = 0; row < numRows; row++){

        for(int column = 0; column < NumCols; column++){

            if(grid[row][column] == 1){

                DrawTexture(Texture, column * cellSize + 1, row * cellSize + 1, WHITE);

            }   
        }
    }
}
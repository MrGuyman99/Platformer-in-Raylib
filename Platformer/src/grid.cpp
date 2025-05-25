#include "grid.hpp"
#include<iostream>
#include "raylib.h"
#include<fstream>
#include<string>

Grid::Grid(){

    numRows = GetScreenHeight() / 32;
    NumCols = GetScreenWidth() / 32;
    //33 or 32, haven't decided
    cellSize = 33;
    Initialize();
    Texture = LoadTexture("Graphics/MetalThing.png");

}

void Grid::Initialize(){

    std::fstream ReadFile;
    ReadFile.open("C:/Users/bodie/OneDrive/Documents/Games/Platformer/Levels/TestLevel.txt");

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
                
                std::cerr << "Unknown tile: " << line[column] << " at row " << row << ", col " << column << std::endl;
                grid[row][column] = 0;
            
            }
        }    
        
        row++;
    }
    
    ReadFile.close();
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
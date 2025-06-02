#pragma once
#include<vector>
#include<raylib.h>
#include<string>

class Grid{

public:
    
    Grid();
    void Initialize();
    void Print();
    int grid[33][60];
    void Draw();
    std::string LevelStuff;
    std::vector<std::string> Levels;

private:

    int numRows;
    int NumCols;
    int cellSize;
    Texture2D Texture;

};
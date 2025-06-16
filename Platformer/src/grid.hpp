#pragma once
#include<vector>
#include "raylib.h"
#include<string>

class Grid{

public:
    
    Grid();
    void Initialize();
    void Print();
    void Draw();
    void Update();
    void MakeWalls(int column, int row);
    int grid[34][60];
    std::string OldLevel;
    std::vector<std::string> Levels;
    int index;
    std::vector<Rectangle> FloorCollisionBoxes;
    std::vector<Rectangle> LeftCollisionBoxes;
    std::vector<Rectangle> RightCollisionBoxes;
    std::vector<Rectangle> BottomCollisionBoxes;
    Texture2D MetalThing;

private:

    float cellSize;
    int numRows;
    int NumCols;

};
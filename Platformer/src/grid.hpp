#pragma once
#include<vector>
#include<raylib.h>
#include<string>

class Grid{

public:
    
    Grid();
    void Initialize();
    void Print();
    void Draw();
    void Update();
    int grid[33][60];
    std::string OldLevel;
    std::vector<std::string> Levels;
    int index;
    int numRows;
    int NumCols;
    std::vector<Rectangle> CollisionBoxes;
    Texture2D MetalThing;

private:

    float cellSize;

};
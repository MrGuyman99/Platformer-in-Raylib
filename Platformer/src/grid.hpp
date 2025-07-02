#pragma once
#include<vector>
#include "raylib.h"
#include<string>

class Grid{

public:
    
    //Methods
    Grid();
    void Initialize();
    void Print();
    void Draw();
    void Update();
    void MakeWalls(int column, int row);
    void RenderUI();

    //Misc. Variables
    int grid[34][60];
    std::string OldLevel;
    std::vector<std::string> Levels;
    int index;
    
    //Vectors of Collision Rectangles
    std::vector<Rectangle> FloorCollisionBoxes;
    std::vector<Rectangle> LeftCollisionBoxes;
    std::vector<Rectangle> RightCollisionBoxes;
    std::vector<Rectangle> BottomCollisionBoxes;
    
    //Textures
    Texture2D MetalThing;
    Texture2D Grass;
    Texture2D Grater;
    Texture2D Chain;
    Texture2D Pipe;
    Texture2D Pipe2;

private:

    float cellSize;
    int numRows;
    int NumCols;

};
#pragma once
#include<vector>
#include "raylib.h"
#include<string>

class Grid{

public:
    
    //Methods
    Grid();
    void Initialize();
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
    std::vector<Texture2D> Textures;


private:

    float cellSize;
    int numRows;
    int NumCols;
    int TileSelected;

};
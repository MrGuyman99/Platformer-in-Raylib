#pragma once
#include<iostream>
#include "raylib.h"
#include "grid.hpp"

class DwarfMan{

public:

    DwarfMan();
    void Draw();
    void Update(bool ShouldFall);
    void HandleInput(Grid& grid);
    Rectangle GetRectFloor();
    Rectangle GetRectWalls();
    Vector2 Position;
    Texture2D TestTexture;

private:
    
    int speed;
    int velocity_y;
    int gravity;
    bool Collided_L;
    bool Collided_R;
    bool Collided_B;
    bool Can_Jump;

};
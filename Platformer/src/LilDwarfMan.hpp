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
    void RenderUI();
    void Animate(Texture2D Texture, int FrameSpeed, int Num_Frames, int StartPos);
    Rectangle GetRectFloor();
    Rectangle GetRectWalls();
    Vector2 Position;
    Texture2D DwarfTexture;

private:
    
    bool Collided_L;
    bool Collided_R;
    bool Collided_B;
    bool Cannot_Jump;
    Vector2 velocity;
    float gravity;
    float speed;
    int CurrentFramePos;
    int FrameCounter;
    std::string WasMoving;

};
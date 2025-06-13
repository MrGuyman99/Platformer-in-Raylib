#pragma once
#include<iostream>
#include "raylib.h"

class DwarfMan{

public:

    DwarfMan();
    void Draw();
    void Update(bool ShouldFall);
    //Love the name so much
    Rectangle GetRect();
    Vector2 Position;

private:
    
    Texture2D TestTexture;
    int speed;
    int velocity_y;
    int gravity;

};
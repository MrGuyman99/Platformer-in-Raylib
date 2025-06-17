#include "raylib.h"
#include<iostream>
#include "LilDwarfMan.hpp"
#include "grid.hpp"

DwarfMan::DwarfMan(){

    //ALL SUBJECT TO CHANGE
    speed = 8;
    velocity_y = 8;
    gravity = 8;
    Position.x = 960;
    Position.y = 540;
    TestTexture = LoadTexture("Graphics/Test.png");
    Collided_R = false;
    Collided_L = false;
    Collided_B = false;

}

void DwarfMan::Draw(){

    DrawTexture(TestTexture, Position.x, Position.y + 5, WHITE);

}

//TODO: Complete refactor/rework (i.e Spliting the gravity and input handling, maybe even an input.cpp?)
void DwarfMan::Update(bool IsNOTOnFloor){

    if(IsNOTOnFloor == true){

        Position.y = Position.y + gravity;

    }

}

void DwarfMan::HandleInput(Grid& grid){

    Collided_R = false;
    Collided_L = false;
    Collided_B = false;

    for(size_t i = 0; i <= grid.LeftCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.LeftCollisionBoxes[i], GetRectWalls())){

            Collided_R = true;
            continue;

        }   

    }

    for(size_t i = 0; i <= grid.RightCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.RightCollisionBoxes[i], GetRectWalls())){

            Collided_L = true;
            continue;

        }

    }

    //Slighty more complicated
    for(size_t i = 0; i <= grid.BottomCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.BottomCollisionBoxes[i], GetRectWalls())){
        
            Collided_B = true;

            //Stops the character from Jittering if you hold up under a tile
            if(IsKeyDown(KEY_UP)){

                Position.y = grid.BottomCollisionBoxes[i].y - 4;

            }   

            continue;

        }
    
    }
    
    if(IsKeyDown(KEY_RIGHT) && Collided_R == false){

        Position.x = Position.x + speed;

    }

    if(IsKeyDown(KEY_LEFT) && Collided_L == false){

        Position.x = Position.x - speed;

    }

    if(IsKeyDown(KEY_UP) && Collided_B == false){

        Position.y = Position.y - 16;

    }

    //DEBUG
    if(IsKeyDown(KEY_R)){

        Position.x = 960;
        Position.y = 540;

    }

}

Rectangle DwarfMan::GetRectFloor(){

    return Rectangle{Position.x + 1, Position.y + TestTexture.height - 1, static_cast<float>(TestTexture.width - 8), 
    static_cast<float>(8)};

}

Rectangle DwarfMan::GetRectWalls(){

    return Rectangle{Position.x, Position.y, static_cast<float>(TestTexture.width), 
    static_cast<float>(TestTexture.height - 8)};

}
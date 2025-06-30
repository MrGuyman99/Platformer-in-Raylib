#include "raylib.h"
#include<iostream>
#include "LilDwarfMan.hpp"
#include "grid.hpp"

DwarfMan::DwarfMan(){

    //ALL SUBJECT TO CHANGE
    speed = 8;
    velocity_y = 8;
    gravity = 4;
    Position.x = 960;
    Position.y = 540;
    TestTexture = LoadTexture("Graphics/Test.png");
    Collided_R = false;
    Collided_L = false;
    Collided_B = false;
    JumpStrength = 16;
    Grid grid = Grid();

}

void DwarfMan::Draw(){

    DrawTexture(TestTexture, Position.x, Position.y + 5, WHITE);

}

void DwarfMan::Update(bool IsNOTOnFloor){

    if(IsNOTOnFloor == true || gravity != 4){

        Position.y = Position.y + gravity;

    }

}

void DwarfMan::Jump(Grid& grid){

    for(size_t i = 0; i <= grid.FloorCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.FloorCollisionBoxes[i], GetRectFloor()) == true){
 

            //So the Jump Code Only Works Once
            break;

        }
    }
}

void DwarfMan::HandleInput(Grid& grid){

    Collided_R = false;
    Collided_L = false;
    Collided_B = false;

    for(size_t i = 0; i <= grid.LeftCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.LeftCollisionBoxes[i], GetRectWalls())){

            Collided_R = true;
            break;

        }   

    }

    for(size_t i = 0; i <= grid.RightCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.RightCollisionBoxes[i], GetRectWalls())){

            Collided_L = true;
            break;

        }

    }

    //Slighty more complicated
    for(size_t i = 0; i <= grid.BottomCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.BottomCollisionBoxes[i], GetRectWalls())){
            
            Position.y = grid.BottomCollisionBoxes[i].y + 4;
            Collided_B = true;
            break;

        }
    
    }
    
    if(IsKeyDown(KEY_RIGHT) && Collided_R == false){

        Position.x = Position.x + speed;

    }

    if(IsKeyDown(KEY_LEFT) && Collided_L == false){

        Position.x = Position.x - speed;

    }

    if(IsKeyDown(KEY_UP) && Collided_B == false){

        //Put Jump Function Here (Below code is temp and ONLY FOR DEBUG)
        //Position.y = Position.y - 16;

        Jump(grid);

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
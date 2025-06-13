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

}

void DwarfMan::Draw(){

    DrawTexture(TestTexture, Position.x, Position.y, WHITE);

}

void DwarfMan::Update(bool IsNOTOnFloor){

    if(IsNOTOnFloor == true){

        Position.y = Position.y + gravity;

    }

}

Rectangle DwarfMan::GetRect(){

    return Rectangle{Position.x, Position.y, static_cast<float>(TestTexture.width), static_cast<float>(TestTexture.height)};

}
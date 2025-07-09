//Libraries
#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

//Headers
#include "LilDwarfMan.hpp"

//C++ Standard 
#include<iostream>

DwarfMan::DwarfMan(){

    //ALL SUBJECT TO CHANGE
    speed = 8.0f;
    velocity = {0, 0};
    gravity = 0.5;
    Position.x = 960;
    Position.y = 540;
    TestTexture = LoadTexture("Graphics/Test.png");
    Collided_R = false;
    Collided_L = false;
    Collided_B = false;
    Cannot_Jump = true;

}

//Draws the DwarfManTexture (TODO: Put animations near here)
void DwarfMan::Draw(){

    DrawTexture(TestTexture, Position.x, Position.y + 5, WHITE);

}

//Updates Gravity, If you can Jump, and adds the velocity to the player 
void DwarfMan::Update(bool IsNOTOnFloor){

    //Increments the velocity to gradually increase the strength of gravity
    velocity.y += gravity;

    //If the player is on the ground & are not trying to jump
    if(IsNOTOnFloor == false && IsKeyPressed(KEY_UP) == false){

        //Stops you from falling
        velocity.y = 0;

    }

    //Adds the current velocity to the position (2D Vector)
    Position = Vector2Add(Position, velocity);
    //Sets Cannot_Jump to equal is IsNOTOnFloor so we can check if the player is on the floor in later parts of the program
    Cannot_Jump = IsNOTOnFloor;

}

void DwarfMan::HandleInput(Grid& grid){

    //Variables
    velocity.x = 0;
    Collided_R = false;
    Collided_L = false;
    Collided_B = false;

    //Checks if the player has collided with the Left Collision Boxes
    for(size_t i = 0; i <= grid.LeftCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.LeftCollisionBoxes[i], GetRectWalls())){

            Collided_R = true;
            break;

        }   

    }

    //Checks if the player has collided with the right
    for(size_t i = 0; i <= grid.RightCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.RightCollisionBoxes[i], GetRectWalls())){

            Collided_L = true;
            break;

        }

    }

    //Slighty more complicated, checks the bottom collisions (Floor Collisions are in main.cpp)
    for(size_t i = 0; i <= grid.BottomCollisionBoxes.size(); i++){

        if(CheckCollisionRecs(grid.BottomCollisionBoxes[i], GetRectWalls())){
            
            Position.y = grid.BottomCollisionBoxes[i].y + 8;
            Collided_B = true;
            break;

        }
    
    }
    
    //Sets the velocity to equal speed (Gets Added in Update())
    if(IsKeyDown(KEY_RIGHT) && Collided_R == false){

        velocity.x = speed;

    }

    //Same, but speed is inverted
    if(IsKeyDown(KEY_LEFT) && Collided_L == false){

        velocity.x = -speed;

    }

    //Jumping code (IsKeyPressed makes sure that it's only called once)
    if(IsKeyPressed(KEY_UP) && Collided_B == false){

        if(Cannot_Jump == false){

            velocity.y = -13;

        }
    
    }

}

//Rectangle for the floor collision box (Probably could combine these but they are just different enough)
Rectangle DwarfMan::GetRectFloor(){

    return Rectangle{Position.x + 1, Position.y + TestTexture.height - 1, static_cast<float>(TestTexture.width - 8), 
    static_cast<float>(8)};

}

//Rectangle for the wall collision box
Rectangle DwarfMan::GetRectWalls(){

    return Rectangle{Position.x, Position.y, static_cast<float>(TestTexture.width), 
    static_cast<float>(TestTexture.height - 8)};

}

void DwarfMan::RenderUI(){

    ImGui::Begin("Dwarf Man Values + Debug");

    if(ImGui::Button("Reset Position", ImVec2(180, 24))){

        Position.x = 960;
        Position.y = 540; 

    }; 

    ImGui::Text("X: %.2f", Position.x);
    ImGui::Text("Y: %.2f", Position.y);
    ImGui::Text("Velocity Y: %.2f", velocity.y);
    ImGui::Text("Velocity X: %0.2f", velocity.x);

    ImGui::End();

}
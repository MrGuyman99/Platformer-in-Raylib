//Libraries
#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

//Headers
#include "LilDwarfMan.hpp"

//C++ Standard 
#include<iostream>
#include<string>

DwarfMan::DwarfMan(){

    //ALL SUBJECT TO CHANGE
    speed = 8.0f;
    velocity = {0, 0};
    gravity = 0.5;
    Position.x = 960;
    Position.y = 540;
    DwarfTexture = LoadTexture("Graphics/DwarfMan.png");
    JumpTexture = LoadTexture("Graphics/JumpFrame.png");
    Collided_R = false;
    Collided_L = false;
    Collided_B = false;
    Cannot_Jump = true;
    CurrentFramePos = 0;
    FrameCounter = 0;
    WasMoving = "Right";

}

//Function for quickly adding animations to DwarfMan (Pass one frame less than you need for Num_Frames)
void DwarfMan::Animate(Texture2D Texture, int FrameSpeed, int Num_Frames, int StartPos){

    FrameCounter++;

    if(FrameCounter >= FrameSpeed){

        CurrentFramePos = CurrentFramePos + 30;
        if(CurrentFramePos > Num_Frames * 30){CurrentFramePos = 0;}
        FrameCounter = 0;

    }

    //Resets the CurrentFramePos if the player releases a key or touches a wall 
    if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)){CurrentFramePos = 0;}
    if(Collided_R == true || Collided_L == true){CurrentFramePos = 0;}

    Rectangle SourcePos = {(float)StartPos + CurrentFramePos, 0, 30.0f, 39};
    DrawTextureRec(Texture, SourcePos, (Vector2){Position.x, Position.y + 5}, WHITE);

}

//Controls the Animations of DwarfMan
void DwarfMan::Draw(){
    
    //Right Running Animation (We pass WasMoving to the idle animation to determine which to play)
    if(velocity.x == speed && velocity.y == 0){

        Animate(DwarfTexture, 4, 3, 120);

    }

    //Left Running Animation
    else if(velocity.x == -speed && velocity.y == 0){

        Animate(DwarfTexture, 4, 3, 240);

    }

    //Left and right idle animations
    else if(velocity.x == 0 && WasMoving == "Right" && velocity.y == 0){Animate(DwarfTexture, 10, 1, 0);}
    else if(velocity.x == 0 && WasMoving == "Left" && velocity.y == 0){Animate(DwarfTexture, 10, 1, 60);}
    //Jump "animations"
    else if(velocity.y != 0 && WasMoving == "Right"){
        
        DrawTextureRec(JumpTexture, (Rectangle){0, 0, 40, 44}, Position, WHITE);
        CurrentFramePos = 0;

    }
    
    else if(velocity.y != 0 && WasMoving == "Left"){
        
        DrawTextureRec(JumpTexture, (Rectangle){40, 0, 40, 44}, Position, WHITE);
        CurrentFramePos = 0;

    }

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

    if(IsNOTOnFloor == true && velocity.y == 0){

        velocity.y = velocity.y + 0.5;

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
            
            velocity.y = 0;
            Collided_B = true;
            break;

        }
    
    }
    
    //Sets the velocity to equal speed (Gets Added in Update())
    if(IsKeyDown(KEY_RIGHT) && Collided_R == false){
        
        velocity.x = speed;
        WasMoving = "Right";

    }   

    //Same, but speed is inverted
    if(IsKeyDown(KEY_LEFT) && Collided_L == false){

        velocity.x = -speed;
        WasMoving = "Left";

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

    return Rectangle{Position.x + 1, Position.y + DwarfTexture.height - 1, static_cast<float>(22), 
    static_cast<float>(8)};

}

//Rectangle for the wall collision box
Rectangle DwarfMan::GetRectWalls(){

    return Rectangle{Position.x, Position.y, static_cast<float>(30), 
    static_cast<float>(DwarfTexture.height - 8)};

}

void DwarfMan::RenderUI(){

    ImGui::Begin("Dwarf Man Values + Debug");

    if(ImGui::Button("Reset Position", ImVec2(180, 24))){

        Position = {960, 540};
        velocity = {0, 0};

    }; 

    ImGui::Text("X: %.2f", Position.x);
    ImGui::Text("Y: %.2f", Position.y);
    ImGui::Text("Velocity Y: %.2f", velocity.y);
    ImGui::Text("Velocity X: %0.2f", velocity.x);

    ImGui::End();

}
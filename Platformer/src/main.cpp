//Libraries
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

//Header Files
#include "grid.hpp"
#include "LilDwarfMan.hpp"

//C++ Standard Library
#include<iostream>

int main(){

    //Raylib Stuff
    SetConfigFlags(FLAG_VSYNC_HINT);
    //SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED); (Use with second monitor)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Lil' Dwarf Game");
    SetTargetFPS(60);

    //ImGui
    rlImGuiSetup(true);

    //Spawning the grid in
    Grid grid = Grid();
    DwarfMan Player = DwarfMan();
    grid.Initialize();

    Color DarkGrey = {42, 43, 42};

    //Game Loop
    while(WindowShouldClose() == false){

        BeginDrawing();
        ClearBackground(DarkGrey);
        //Drawing all the members of the Grid =! 0
        grid.Draw();
        Player.Draw();

        rlImGuiBegin();
        Player.RenderUI();
        grid.RenderUI();
        rlImGuiEnd();

        EndDrawing();
        grid.Update();
        Player.HandleInput(grid);

        //Collision Code (TODO: OOP This son of a b*tch)
        bool fall = true;

        for(size_t i = 0; i <= grid.FloorCollisionBoxes.size(); i++){

            if(CheckCollisionRecs(grid.FloorCollisionBoxes[i], Player.GetRectFloor()) == true){

                Player.Update(false);
                fall = false;
                
                if(IsKeyPressed(KEY_UP) == false){

                    Player.Position.y = grid.FloorCollisionBoxes[i].y - 45;

                }
                
                break;

            }

            //This is so the player doesn't fall ridiculously fast
            if(i == grid.FloorCollisionBoxes.size() && fall == true){

                Player.Update(true);

            }

        }


    }

    //Deconstructers (Bugged Ouit when I tried to OOP them so I just slapped them here)
    UnloadTexture(grid.MetalThing);
    UnloadTexture(grid.Grass);
    UnloadTexture(grid.Grater);
    UnloadTexture(grid.Pipe);
    UnloadTexture(grid.Pipe2);
    UnloadTexture(Player.TestTexture);
    rlImGuiShutdown();
    CloseWindow();

}
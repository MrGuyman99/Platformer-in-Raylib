#include "raylib.h"
#include<iostream>
#include "grid.hpp"
#include "LilDwarfMan.hpp"

int main(){

    //Raylib Stuff
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Lil' Dwarf Game");
    SetTargetFPS(60);

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

        EndDrawing();
        grid.Update();
        
        //This code is DISGUSTING but I need a goddamn break aight
        bool fall = true;

        for(size_t i = 0; i <= grid.CollisionBoxes.size(); i++){

            if(CheckCollisionRecs(grid.CollisionBoxes[i], Player.GetRect()) == true){

                Player.Update(false);
                fall = false;

            }
            
            if(i == grid.CollisionBoxes.size() && fall == true){

                Player.Update(true);

            }
        }
    }

    UnloadTexture(grid.MetalThing);
    CloseWindow();

}
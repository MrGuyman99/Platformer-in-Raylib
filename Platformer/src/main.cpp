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
        Player.HandleInput(grid);

        //Collision Code (TODO: OOP This son of a b*tch)
        bool fall = true;
        
        for(size_t i = 0; i <= grid.FloorCollisionBoxes.size(); i++){

            if(CheckCollisionRecs(grid.FloorCollisionBoxes[i], Player.GetRectFloor()) == true){

                Player.Update(false);
                fall = false;

            }

            //This is so the player doesn't fall ridiculously fast 
            if(i == grid.FloorCollisionBoxes.size() && fall == true){

                Player.Update(true);

            }
        
        }       
    
    }

    //Deconstructers
    UnloadTexture(grid.MetalThing);
    UnloadTexture(grid.Grass);
    UnloadTexture(grid.Grater);
    UnloadTexture(Player.TestTexture);
    CloseWindow();

}
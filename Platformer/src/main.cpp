#include "raylib.h"
#include<iostream>
#include "grid.hpp"

int main(){

    //Raylib Stuff
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1920, 1080, "Lil' Dwarf Game");
    SetTargetFPS(60);

    //Spawning the grid in
    Grid grid = Grid();
    grid.Print();
    
    //Game Loop
    while(WindowShouldClose() == false){

        BeginDrawing();
        ClearBackground(BLACK);
        //Drawing all the members of the Grid =! 0
        grid.Draw();
        
        EndDrawing();

    }

    CloseWindow();

}
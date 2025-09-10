#include "raylib.h"

int main()
{
    //Screen Initalization
    int width = 800;
    int height = 450;
    int width_half = width/2;
    int height_half = height/2;

    int r_width = 50;
    int r_height = 80;

    int posY = height - r_height;
    int velocity = 0;

    //Creating Window                            
    InitWindow(width, height, "Endless Runner 2D");

    //Limit FPS
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //Game Logic Starts
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        posY += velocity;

        DrawRectangle(width_half, posY, r_width, r_height, BLUE);

        //Game Logic Ends
        EndDrawing();
    }
    CloseWindow();
}
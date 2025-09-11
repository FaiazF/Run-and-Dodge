#include "raylib.h"

int main()
{
    //Screen Initalization
    const int width = 800;
    const int height = 450;
    const int width_half = width/2;
    const int height_half = height/2;

    //Character height and width
    const int r_width = 50;
    const int r_height = 80;

    //Character Jumping
    int posY = height - r_height;
    int velocity = 0;
    const int jumpVelocity = -22;

    //acceletation due to gravity (pixels/frame)/frame
    int gravity = 1;
    
    //Is Character in the air?
    bool isInAir;


    //Creating Window                            
    InitWindow(width, height, "Endless Runner 2D");

    //Limit FPS
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //Game Logic Starts
        BeginDrawing();
        ClearBackground(WHITE);

        //Perform Ground Check
        if (posY >= height - r_height)
        {
            //Character on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //Character in air
            //Apply gravity
            velocity += gravity;
            isInAir = true;
        }

        if ( (IsKeyPressed(KEY_SPACE)) && (isInAir == false) )
        {
            velocity += jumpVelocity;
        }

        //Updating Position
        posY += velocity;

        DrawRectangle(width_half, posY, r_width, r_height, BLUE);

        //Game Logic Ends
        EndDrawing();
    }
    CloseWindow();
}
#include "raylib.h"

int main()
{
    //Screen Initalization
    const int width = 800;
    const int height = 450;
    const int width_half = width/2;

    //Creating Window                            
    InitWindow(width, height, "Endless Runner 2D");

    //Character Jumping (pixels/sec)
    int velocity = 0;
    const int jumpVelocity = -800;

    //Character acceletation due to gravity (pixels/sec)/sec
    int gravity = 1'500;

    //Obstacle Drawing
    Texture2D Obstacle = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle ObstacleRec{0.0, 0.0, Obstacle.width/8, Obstacle.height/8}; //(x, y, width, height)
    Vector2 ObstaclePos{width, height - ObstacleRec.height}; //(x, y)

    //Obstacle X velocity (pixels/sec)
    int ObstacleVelocity{-200};

    //Character Drawing
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0.0, 0.0, scarfy.width/6, scarfy.height}; // (x, y, width, height)
    Vector2 scarfyPos{width_half - scarfyRec.width/2, height -scarfyRec.height}; //(x, y)

    //Obstacle Animation Frame
    int ObstacleFrame;

    //Amount of time before we update the character animation frame
    const float ObstacleUpdateTime = 1.0/12.0;
    float ObstacleRunningTime;

    //Character Animation Frame
    int frame;

    //Amount of time before we update the character animation frame
    const float updateTime = 1.0/12.0;
    float runningTime;
    
    //Is Character in the air?
    bool isInAir;

    //Limit FPS
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //Delta time (time since last frame)
        const float dT = GetFrameTime();

        //Game Logic Starts
        BeginDrawing();
        ClearBackground(WHITE);

        //Perform Ground Check
        if (scarfyPos.y >= height - scarfyRec.height)
        {
            //Character on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //Character in air
            //Apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        if ( (IsKeyPressed(KEY_SPACE)) && (!isInAir) )
        {
            velocity += jumpVelocity;
        }

        //Updating Obstacle Position
        ObstaclePos.x += ObstacleVelocity * dT;
        
        //Updating Character Position
        scarfyPos.y += velocity * dT;

        //Updating Character Running Time
        if (!isInAir)
        {
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                //Update Character Animation Frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
                
            }
        }

        // Updating Obstacle Running Time
        ObstacleRunningTime += dT;
        if (ObstacleRunningTime >= ObstacleUpdateTime)
        {
            ObstacleRunningTime = 0.0;
            //Update Obstacle Animation Frame
            ObstacleRec.x = ObstacleFrame * ObstacleRec.width;
            ObstacleFrame++;
            if (ObstacleFrame > 7)
            {
                ObstacleFrame = 0;
            }
        }

        //Draw Obstacle
        DrawTextureRec(Obstacle, ObstacleRec, ObstaclePos, WHITE);
        
        //Draw Character
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(Obstacle);
    CloseWindow();
}
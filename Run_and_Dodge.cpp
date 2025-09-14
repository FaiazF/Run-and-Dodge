#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;

};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    //Update Running Time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //Update Animation Frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    //Screen Initalization
    int windowDimensions[2];
    windowDimensions[0] = 800;
    windowDimensions[1] = 450;

    //Creating Window                            
    InitWindow(windowDimensions[0], windowDimensions[1], "Run and Dodge");

    //Character Jumping (pixels/sec)
    int velocity = 0;
    const int jumpVelocity = -800;

    //Character acceletation due to gravity (pixels/sec)/sec
    int gravity = 1'500;

    //Obstacle Variables
    Texture2D Obstacle = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfObstacleArray{6};
    AnimData ObstacleArray[sizeOfObstacleArray] {};

    for (int i = 0; i < sizeOfObstacleArray; i++)
    {
        ObstacleArray[i].rec.x = 0.0;
        ObstacleArray[i].rec.y = 0.0;
        ObstacleArray[i].rec.width = Obstacle.width/8;
        ObstacleArray[i].rec.height = Obstacle.height/8;

        ObstacleArray[i].pos.x = windowDimensions[0] + (i * 300);
        ObstacleArray[i].pos.y = windowDimensions[1] - Obstacle.height/8;

        ObstacleArray[i].frame = 0.0;

        ObstacleArray[i].updateTime = 1.0/16.0;

        ObstacleArray[i].runningTime = 0.0;
    }

    //Obstacle X velocity (pixels/sec)
    int ObstacleVelocity{-200};

    //Character Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData
    {
        {0.0, 0.0, scarfy.width/6, scarfy.height}, //Rectangle
        {windowDimensions[0]/2 - (scarfy.width/6)/2, windowDimensions[1] - scarfy.height}, //Pos
        0, //frame
        1.0/12.0, //updateTime
        0.0 //runningTime
    };
    
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
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        //Updating Obstacles Position
        for ( int i = 0; i < sizeOfObstacleArray; i++)
        {
            ObstacleArray[i].pos.x += ObstacleVelocity * dT;
        }
        
        //Updating Character Position
        scarfyData.pos.y += velocity * dT;

        //Updating Character Running Time
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        // Updating Obstacles Running Time
        for ( int i = 0; i < sizeOfObstacleArray; i++)
        {
            ObstacleArray[i] = updateAnimData(ObstacleArray[i], dT, 7);
        }

        //Draw Obstacles
        for ( int i = 0; i < sizeOfObstacleArray; i++)
        {
            DrawTextureRec(Obstacle, ObstacleArray[i].rec, ObstacleArray[i].pos, WHITE);
        }
        
        
        //Draw Character
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(Obstacle);
    CloseWindow();
}
/****************************************************************************************************
*** File Name:      dappy_dasher.cpp
*** Description:    A short 2D runner game to dodge obsticles and reach the finish line
*** Author:         Trevor Carson
*** Date:           2021-08-25
*****************************************************************************************************/

#include "raylib.h"

// Structure to hold various information for animating sprite sheets
struct AnimationData {
    Rectangle rectangle;    // Rectangle to map out sprite sheet
    Vector2 position;       // Vector for coordinates on screen
    int frameX;             // Integer used to keep track of the current sprite sheet frame row
    int frameY;             // Integer used to keep track of the current sprite sheet frame column
    float updateTime;       // Time passed in between each animation frame (updates x/second)
    float runningTime;      // Float to hold the current time since last frame change
};

// Function to check if Scarfy is on the ground
bool isOnGround(AnimationData data, int windowHeight) {
    return data.position.y >= windowHeight - data.rectangle.height;
}

// Function to update running time and animation frame for Scarfy's sprite sheet
AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrameX) {
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime) {
        data.runningTime = 0.0f;
        data.rectangle.x = (data.frameX * data.rectangle.width);
        data.frameX++;

        if (data.frameX > maxFrameX) {
            data.frameX = 0;
        }
    }
    return data;
} 

// Function to update running time and animation frame for the Nebulae's sprite sheet
AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrameX, int maxFrameY, int lastFrameX) {
    data.runningTime += deltaTime;
            
    if (data.runningTime >= data.updateTime) {
        data.runningTime = 0.0f;
        data.rectangle.x = (data.frameX * data.rectangle.width);
        data.rectangle.y = (data.frameY * data.rectangle.height);
        data.frameX++;

        if (data.frameY == maxFrameY && data.frameX == lastFrameX) {
            data.frameX = 0;
            data.frameY = 0;
        }
                    
        if (data.frameX > maxFrameX) {
            data.frameX = 0;
            data.frameY++;

            if (data.frameY > maxFrameY) {
                data.frameY = 0;
            }
        }
    }
    return data;
} 

// Main method for Dapper Dasher game
int main() {
    /// Game Window Settings
    float const windowDimentions[2]{800.0f, 600.0f};    // Integer array to store window breadth and height
    InitWindow(windowDimentions[0], windowDimentions[1], "Dapper Dasher");
    SetTargetFPS(60);

    /// Nebula(obsticle) Settings
    int const nebulaVelocity{-200};             // Nebula -X screen speed (pixels/frame)
    Texture2D nebula{LoadTexture("textures\\12_nebula_spritesheet.png")};   // Texture to hold nebula sprite sheet
    int const numberOfNebulae{10};              // Integer to hold number of nebulae to spawn in the level
    AnimationData nebulae[numberOfNebulae]{};   // Array for number[x] of nebulae in lvl
    
    for (int i =0; i < numberOfNebulae; i++) {
        nebulae[i].rectangle.x = 0.0f;
        nebulae[i].rectangle.y = 0.0f;
        nebulae[i].rectangle.width = (nebula.width / 8.0f);
        nebulae[i].rectangle.height = (nebula.height / 8.0f);
        nebulae[i].position.x = windowDimentions[0] + nebulae[0].position.x + i * 300;
        nebulae[i].position.y = (windowDimentions[1] - (nebula.height / 8));
        nebulae[i].frameX = 0;
        nebulae[i].frameY = 0;
        nebulae[i].updateTime = (1.0f / 32.0f);
        nebulae[i].runningTime = 0.0f;
    }

    /// Finish Line Settings (Win/Lose)
    float finishLine{nebulae[numberOfNebulae - 1].position.x + 10.0f};  // Flost to hold the location of the levels finish line
    bool collision{};                                                   // Boolean default false (win/lose condition)

    /// Character Settings (Scarfy)
    int const gravity{1'000};       // Gravity rounded up from 9.8m/s (pixels/s)/s
    int const jumpVelocity{-600};   // Jump strength (pixels/s)
    int rectangleVelocity{0};       // Sets the velocity of the rectangle
    bool isInAir{false};            // Check if character is currently in the air
    Texture2D scarfy{LoadTexture("textures\\scarfyEvil.png")};  // Texture to hold characters sprite sheet
    AnimationData scarfyData{
        {0.0f, 0.0f, (scarfy.width / 6.0f), (scarfy.height * 1.0f)},
        {((windowDimentions[0] / 2.0f) - (scarfyData.rectangle.width / 2.0f)), (windowDimentions[1] - scarfyData.rectangle.height)},
        0,
        0,
        (1.0f / 12.0f),
        0.0f
    };                              // Animationdata structure for Scarfy

    /// Scene Settings
    Texture2D background = LoadTexture("textures\\far-buildings.png");
    float backgroundX{0.0f};
    float backgroundScrollSpeed{20.0f};
    float backgroundScale{3.2f};
    Texture2D midground = LoadTexture("textures\\back-buildings.png");
    float midgroundX{0.0f};
    float midgroundScrollSpeed{40.0f};
    float midgroundScale{3.2f};
    Texture2D foreground = LoadTexture("textures\\foreground.png");
    float foregroundX{0.0f};
    float foregroundScrollSpeed{80.0f};
    float foregroundScale{3.2f};

    /// Games main loop (exits on ESC or default window X)
    while (!WindowShouldClose()) {
        float deltaTime{GetFrameTime()};    // Delta time is the change in time based on frame rate (since last frame)
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        backgroundX -= (backgroundScrollSpeed * deltaTime);
        midgroundX -= (midgroundScrollSpeed * deltaTime);
        foregroundX -= (foregroundScrollSpeed * deltaTime);
        
        if (backgroundX <= (-background.width * backgroundScale)) {
            backgroundX = 0.0f;
        }
        
        if (midgroundX <= (-midground.width * midgroundScale)) {
            midgroundX = 0.0f;
        }
        
        if (foregroundX <= (-foreground.width * foregroundScale)) {
            foregroundX = 0.0f;
        }

        Vector2 backgroundPosition1{backgroundX, 0.0f};                             // Vector to store the coordinates for the background position
        DrawTextureEx(background, backgroundPosition1, 0.0f, backgroundScale, WHITE);
        Vector2 backgroundPosition2{(backgroundX + background.width * 3.2f), 0.0f}; // Vector to store the coordinates for the background2 position
        DrawTextureEx(background, backgroundPosition2, 0.0f, backgroundScale, WHITE);
        Vector2 midgroundPosition1{midgroundX, 0.0f};                               // Vector to store the coordinates for the midground position
        DrawTextureEx(midground, midgroundPosition1, 0.0f, midgroundScale, WHITE);
        Vector2 midgroundPosition2{(midgroundX + midground.width * 3.2f), 0.0f};    // Vector to store the coordinates for the midground2 position
        DrawTextureEx(midground, midgroundPosition2, 0.0f, midgroundScale, WHITE);
        Vector2 foregroundPosition1{foregroundX, 0.0f};                             // Vector to store the coordinates for the foreground position
        DrawTextureEx(foreground, foregroundPosition1, 0.0f, foregroundScale, WHITE);
        Vector2 foregroundPosition2{(foregroundX + foreground.width * 3.2f), 0.0f}; // Vector to store the coordinates for the foreground2 position
        DrawTextureEx(foreground, foregroundPosition2, 0.0f, foregroundScale, WHITE);

        for (int i = 0; i < numberOfNebulae; i++) {
            nebulae[i] = updateAnimationData(nebulae[i], deltaTime, 7, 7, 4);
        }     
        
        if (!isInAir) {
            scarfyData = updateAnimationData(scarfyData, deltaTime, 5);
        }
        
        if (isOnGround(scarfyData, windowDimentions[1])) {
            rectangleVelocity = 0;
            isInAir = false;
        } else {
            rectangleVelocity += gravity * deltaTime;
            isInAir = true;
        }
        
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            rectangleVelocity += jumpVelocity;
        }
        
        for (AnimationData nebula : nebulae) {
            float nebulaPadding{50};    // Float to make the collision accurate because of white space on spritesheet
            Rectangle nebulaRectangle{
                nebula.position.x + nebulaPadding,
                nebula.position.y + nebulaPadding,
                nebula.rectangle.width - (2 * nebulaPadding),
                nebula.rectangle.height - (2 * nebulaPadding)
            };                          // Rectangle for nebula collision
            Rectangle scarfyRectangle{
                scarfyData.position.x,
                scarfyData.position.y,
                scarfyData.rectangle.width,
                scarfyData.rectangle.height
            };                          // Rectangle for Scarfy collision
            if (CheckCollisionRecs(nebulaRectangle, scarfyRectangle)) {
                collision = true;
            }
        }

        scarfyData.position.y += rectangleVelocity * deltaTime;
        finishLine += (nebulaVelocity * deltaTime);

        for (int i = 0; i < numberOfNebulae; i++) {
            nebulae[i].position.x += nebulaVelocity * deltaTime;
        }
        
        if (collision) {
            DrawText("Game Over!", windowDimentions[0] / 2 - 265, windowDimentions[1] / 2, 100, RED);
        } else {
            for (int i = 0; i < numberOfNebulae; i++) {
                DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].position, WHITE);
            }
            DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.position, WHITE);
            if (scarfyData.position.x >= finishLine) {
                DrawText("You Win!", windowDimentions[0] / 2 - 200, windowDimentions[1] / 2, 100, GREEN);
            }
        }

        EndDrawing();
    }
    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    return 0;   // Default errorless return value to show program executed properly
}

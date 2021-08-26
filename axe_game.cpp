/****************************************************************************************************
*** File Name:      axe_game.cpp
*** Description:    Program to move a dot around the screen and not get hit by the moving block
*** Author:         Trevor Carson
*** Date:           2021-08-21
*****************************************************************************************************/

#include "raylib.h"

int main() {
    int windowBreadth{800};   // Window width
    int windowHeight{600};    // Window height
    InitWindow(windowBreadth, windowHeight, "Axe Game");

    int circleX{400};       // Starting X position for the circle
    int circleY{300};       // Starting Y position for the circle
    int circleRadius{25};   // Starting radius for the circle
    int circleLeftCollision{circleX - circleRadius};    // Circles left collision
    int circleRightCollision{circleX + circleRadius};   // Circles right collision
    int circleTopCollision{circleY - circleRadius};     // Circles top collision
    int circleBottomCollision{circleY + circleRadius};  // Circles bottom collision

    int rectangleX{300};        // Starting X position for the rectangle
    int rectangleY{60};         // Starting Y position for the rectangle
    int rectangleBreadth{50};   // Starting width for the rectangle
    int rectangleHeight{50};    // Starting height for the rectangle
    int rectangleDirection{10}; // Starting rectangle direction
    int rectangleLeftCollision{rectangleX};                     // Rectangles left collision
    int rectangleRightCollision{rectangleX + rectangleBreadth};  // Rectangles right collision
    int rectangleTopCollision{rectangleY};                     // Rectangles top collision
    int rectangleBottomCollision{rectangleY + rectangleHeight};  // Rectangles bottom collision

    // Boolean to track circle and rectangle collision
    bool bHasCollisionWithAxe =
                        (rectangleBottomCollision >= circleTopCollision) &&
                        (rectangleTopCollision <= circleBottomCollision) &&
                        (rectangleRightCollision >= circleLeftCollision) &&
                        (rectangleLeftCollision <= circleRightCollision);

    SetTargetFPS(60);
    
    while (WindowShouldClose() != true) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        circleLeftCollision = circleX - circleRadius;
        circleRightCollision = circleX + circleRadius;
        circleTopCollision = circleY - circleRadius;
        circleBottomCollision = circleY + circleRadius;

        rectangleLeftCollision = rectangleX;
        rectangleRightCollision = rectangleX + rectangleBreadth;
        rectangleTopCollision = rectangleY;
        rectangleBottomCollision = rectangleY + rectangleHeight;

        bHasCollisionWithAxe =
                        (rectangleBottomCollision >= circleTopCollision) &&
                        (rectangleTopCollision <= circleBottomCollision) &&
                        (rectangleRightCollision >= circleLeftCollision) &&
                        (rectangleLeftCollision <= circleRightCollision);

        DrawCircle(circleX, circleY, circleRadius, BLUE);
        DrawRectangle(rectangleX, rectangleY, rectangleBreadth, rectangleHeight, RED);

        if (bHasCollisionWithAxe) {
            DrawText("Game Over!", windowBreadth / 2 - 50, windowHeight / 2, 20, RED);
        } else {
            rectangleY += rectangleDirection;

            if (rectangleY == (windowHeight - rectangleHeight) || rectangleY == (0)) {
                rectangleDirection = -rectangleDirection;
            }

            if (IsKeyDown(KEY_RIGHT) && circleX < (windowBreadth - circleRadius)) {
                circleX = circleX + 10;
            }
            if (IsKeyDown(KEY_LEFT) && circleX > (0 + circleRadius)) {
                circleX = circleX - 10;
            }
            if (IsKeyDown(KEY_UP) && circleY > (0 + circleRadius)) {
                circleY = circleY - 10;
            }
            if (IsKeyDown(KEY_DOWN) && circleY < (windowHeight - circleRadius)) {
                circleY = circleY + 10;
            }
        }
        EndDrawing();
    }
}

#include <iostream>
#include <raylib.h>
#include "playervsbot.hpp"

using namespace std;

int main() {
   
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Ping Pong");

    // Button properties, button = pvbButton
    Rectangle button = { 330, 520, 300, 50 };  // Position and size of the button
    Color buttonColor = LIGHTGRAY;              // Default button color
    Color buttonHoverColor = DARKGRAY;          // Button color when hovering
    Color buttonClickColor = GRAY;              // Button color when clicked

    bool buttonClicked = false;                 // To track if the button was clicked

    //pvpButton
    Rectangle pvpButton = {1290, 520, 300, 50}; //xy pos & xy size of pvpButton
    Color pvpButtonColor = LIGHTGRAY;
    Color pvpHoverColor = DARKGRAY;
    Color pvpClickColor = GRAY;

    bool pvpButtonClicked = false;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 mousePosition = GetMousePosition(); // Get current mouse position

        // Check if the mouse is hovering over the buttons
        bool isHovering = CheckCollisionPointRec(mousePosition, button);
        bool pvpButtonisHovering = CheckCollisionPointRec(mousePosition, pvpButton);

        // Change button color based on mouse state
        if (isHovering) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                buttonColor = buttonClickColor;  // Button clicked
                buttonClicked = true;
            } else {
                buttonColor = buttonHoverColor;  // Button hovered
            }
        } else {
            buttonColor = LIGHTGRAY;  // Default button color
        }

        if (pvpButtonisHovering) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                pvpButtonColor = pvpClickColor;  // Button clicked
                pvpButtonClicked = true;
            } else {
                pvpButtonColor = pvpHoverColor;  // Button hovered
            }
        } else {
            pvpButtonColor = LIGHTGRAY;  // Default button color
        }


        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the button
        DrawRectangleRec(button, buttonColor);
        DrawRectangleRec(pvpButton, pvpButtonColor);


        // Draw the button text
        DrawText("Ping Pong", screenWidth/2 - 215, 180, 80, WHITE);

        DrawText("Player Vs Bot", button.x + 60, button.y + 15, 20, BLACK);
        DrawText("Player Vs Player", pvpButton.x + 60, pvpButton.y + 15, 20, BLACK);


        // Display the result of the button click
        if (buttonClicked) {
            PlayVsBot();
        }
        if (pvpButtonClicked) {
            PlayVsPlayer();
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

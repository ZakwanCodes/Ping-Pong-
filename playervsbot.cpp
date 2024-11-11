#include <iostream>
#include <raylib.h>
using namespace std;

// Global variables for scores
int player_score = 0;
int cpu_score = 0;

// Define colors
Color Blue = Color{30, 144, 255, 255};        // Bright Blue g
Color Dark_Blue = Color{0, 0, 139, 255};      // Dark Blue dg
Color Light_Blue = Color{173, 216, 230, 255}; // Light Sky Blue lg
Color Pink = Color{255, 105, 180, 255};       // Hot Pink y


// Ball class
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, Pink);
    }

    void Update() {
        x += speed_x;
        y += speed_y;
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) { // CPU wins
            cpu_score++;
            ResetBall();
            ResetPaddles();
        }
        if (x - radius <= 0) { // Player wins
            player_score++;
            ResetBall();
            ResetPaddles();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }

    void ResetPaddles();
};

// Paddle class
class Paddle {
public:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        LimitMovement();
    }

    // Method to reset the paddle position
    void ResetPosition(float new_x, float new_y) {
        x = new_x;
        y = new_y;
    }
};

// CpuPaddle class
class CpuPaddle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y) {
            y = y + speed;
        }
        LimitMovement();
    }

    // Reset the CPU paddle's position
    void ResetPosition() {
        Paddle::ResetPosition(10, GetScreenHeight() / 2 - height / 2);
    }
};

// Global instances
Ball ball;
Paddle player;
CpuPaddle cpu;

// Implement ResetPaddles function
void Ball::ResetPaddles() {
    player.ResetPosition(GetScreenWidth() - player.width - 10, GetScreenHeight() / 2 - player.height / 2);
    cpu.ResetPosition();
}

// PlayvsBot
void PlayVsBot(){
    const int screen_width = 1920;
    const int screen_height = 1080;
    InitWindow(screen_width, screen_height, "Ping Pong");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 10;
    ball.speed_y = 10;

    player.width = 25;
    player.height = 160;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 10;

    cpu.width = 25;
    cpu.height = 160;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 10;

    while (!WindowShouldClose()) {
        // Update
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check for collisions
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(Dark_Blue);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Blue);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Blue);
        BeginDrawing();
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    CloseWindow();
}

void PlayVsPlayer() {
    const int screen_width = 1920;
    const int screen_height = 1080;
    InitWindow(screen_width, screen_height, "Ping Pong");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 10;
    ball.speed_y = 10;

    player.width = 25;
    player.height = 160;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 10;

    cpu.width = 25;
    cpu.height = 160;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 10;

    // In the PlayVsPlayer function, update controls
while (!WindowShouldClose()) {
    // Update
    ball.Update();
    player.Update();

    // For the second player
    if (IsKeyDown(KEY_A)) {
        cpu.y -= cpu.speed;  // Move up
    }
    if (IsKeyDown(KEY_D)) {
        cpu.y += cpu.speed;  // Move down
    }
    cpu.LimitMovement(); // Ensure paddle stays within bounds

    // Check for collisions
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
        ball.speed_x *= -1;
    }
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
        ball.speed_x *= -1;
    }


    // Drawing
    ClearBackground(Dark_Blue);
    DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Blue);
    DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Blue);
    BeginDrawing();
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();
    DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
    EndDrawing();
    }
    CloseWindow();
}
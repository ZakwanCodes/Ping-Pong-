#ifndef PLAYERVSBOT_HPP
#define PLAYERVSBOT_HPP

#include <raylib.h>

// Global variables for scores
extern int player_score;
extern int cpu_score;

// Define colors
extern Color Green;
extern Color Dark_Green;
extern Color Light_Green;
extern Color Yellow;

// Ball class
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw();
    void Update();
    void ResetBall();
    void ResetPaddles();
};

// Paddle class
class Paddle {
public:
    void LimitMovement();
public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    void Update(bool isPlayer1);
    void ResetPosition(float new_x, float new_y);
};

// CpuPaddle class
class CpuPaddle : public Paddle {
public:
    void Update(int ball_y);
    void ResetPosition();
};

extern Ball ball;
extern Paddle player;
extern Paddle player2; // For player vs player
extern CpuPaddle cpu;

// Game functions
void PlayVsBot();
void PlayVsPlayer();

#endif // PLAYERVSBOT_HPP


#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "food.hpp"
#include "snake.hpp"
#include"sound.hpp"
// dividing the game window 750 into small cells
const int cellSize = 30;
const int cellCount = 25;
const int offset = 75;
// 30*25 = 750
int score = 0;
double lastupdateTime = 0;
bool triggerEvent(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastupdateTime >= interval)
    {
        lastupdateTime = currentTime;
        return true;
    }
    return false;
}
sound snd = sound();
void manupulate_snake(Snake &snake)
{
     if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) // Prevent reversing direction
    {
        snake.direction = {0, -1};
        snake.runing = true; // Start the game
    }
    else if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
    {
        snake.direction = {0, 1};
        snake.runing = true;
    }
    else if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
    {
        snake.direction = {-1, 0};
        snake.runing = true;
    }
    else if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
    {
        snake.direction = {1, 0};
        snake.runing = true;
    }
}

bool check_same_location(Vector2 foodPos, Snake snake)
{
    for (unsigned int i = 0; i < snake.body.size(); i++)
    {
        if (Vector2Equals(foodPos, snake.body[i]))
        {
            return true;
        }
    }
    return false;
}
void checkCollisionWithFood(Snake &snake, Food &food)
{
    if (Vector2Equals(snake.body[0], food.position))
    {
        Vector2 pos = food.GetFoodPos();
        while (check_same_location(pos, snake) == true)
        {
            pos = food.GetFoodPos();
        }
        food.position = pos;
        snake.snakeAddSegment = true;
        PlaySound(snd.eatSound);
        score++;
    }
}
Vector2 getNewPos(Snake &snake, Food &food)
{
    float x = GetRandomValue(0, 24);
    float y = GetRandomValue(0, 24);
    Vector2 pos = {x, y};
    while (check_same_location(pos, snake) == true)
    {
        x = GetRandomValue(0, 24);
        y = GetRandomValue(0, 24);
    }
    return pos;
}
void checkCollisionWithEdges(Snake &snake, Food &food)
{
    if (snake.body[0].x == cellCount || snake.body[0].x == -1)
    {
        snake.gameOver();
        food.position = getNewPos(snake, food);
        snake.runing = false;
        score = 0;
        PlaySound(snd.wallSound);
    }
    if (snake.body[0].y == cellCount || snake.body[0].y == -1)
    {
        snake.gameOver();
        food.position = getNewPos(snake, food);
        snake.runing = false;
        score = 0;
        PlaySound(snd.wallSound);
    }
}

bool ElementInDequeue(Vector2 head,deque<Vector2> body)
{
    for(unsigned int i = 0 ; i < body.size() ; i++)
    {
        if(Vector2Equals(body[i],head))
        {
            return true;
        }
    }
    return false;
}

void checkCollisionWithTail(Snake &snake)
{
    deque<Vector2> healessBody = snake.body;
    healessBody.pop_front();
    if(ElementInDequeue(snake.body[0],healessBody))
    {
        snake.gameOver();
        snake.runing = false;
        PlaySound(snd.wallSound);
        score = 0;
    }

}
using namespace std;
int main()
{
    Color green = {173, 204, 96, 255};
    Color darkGreen = {43,51,24,255};
    cout << "Running the game ...." << endl;
    InitWindow(2*offset+cellSize * cellCount,2*offset+ cellSize * cellCount, "RETRO SNAKE");
    SetTargetFPS(60);
    Food food = Food();
    Snake snake = Snake();
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        if (snake.runing == true)
        {
            if (triggerEvent(0.2) == true)
            {
                snake.update();
            }
        }
        manupulate_snake(snake);
        checkCollisionWithFood(snake, food);
        checkCollisionWithEdges(snake, food);
        checkCollisionWithTail(snake);
        ClearBackground(green);
        food.Draw();
        DrawRectangleLinesEx(Rectangle{(float)offset-5,(float)offset-5,(float)cellSize*cellCount+10,(float)cellSize*cellCount+10},5,darkGreen);
        snake.Draw();
        DrawText("RETRO SNAKE",300,20,40,darkGreen);
        DrawText(TextFormat("%i",score),420,offset+cellSize*cellCount+15,45,darkGreen);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
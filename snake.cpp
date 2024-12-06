#include <raylib.h>
#include <iostream>
#include <deque>
#include "snake.hpp"
#include <raymath.h>
using namespace std;
Snake::Snake()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    snakeAddSegment = false;
}
void Snake::Draw()
{
    for (unsigned int i = 0; i < body.size(); i++)
    {
        Rectangle segment = {75+body[i].x * 30,75+ body[i].y * 30, 30, 30};
        DrawRectangleRounded(segment, 0.5, 6, {43, 51, 24, 255});
    }
}
void Snake::update()
{
    if (snakeAddSegment == true)
    {
        body.push_front(Vector2Add(body[0], direction));
        snakeAddSegment = false;
    }
    else
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }
}

void Snake::gameOver()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    
}
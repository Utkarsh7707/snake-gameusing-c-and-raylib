#include"food.hpp"
#include<stdio.h>
#include<raylib.h>

Food::Food()
{
    position = GetFoodPos();
    image = LoadTexture("/home/utkarsh/Desktop/c++ games/snake_game/Graphics/food.png");
}
Food::~Food()
{
    UnloadTexture(image);
}
void Food::Draw()
{
    DrawTexture(image,75+position.x*30,75+position.y*30,WHITE);
}
Vector2 Food::GetFoodPos()
{
    float x = GetRandomValue(0,24);
    float y = GetRandomValue(0,24);
    return Vector2{x,y};
}
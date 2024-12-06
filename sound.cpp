#include"sound.hpp"
#include<raylib.h>

sound::sound()
{
    InitAudioDevice();
    eatSound = LoadSound("/home/utkarsh/Desktop/c++ games/snake_game/sounds/eat.mp3");
    wallSound = LoadSound("/home/utkarsh/Desktop/c++ games/snake_game/sounds/wall.mp3");
}

sound::~sound()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}
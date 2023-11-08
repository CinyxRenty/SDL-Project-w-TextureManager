#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace Game
{
    bool Init();
    bool InitSubsystems();
    void CleanUp();
    void CreateWindow();
    void CreateRenderer();
    void LoadTextures();
    void Render();
    void GameLoop();
}

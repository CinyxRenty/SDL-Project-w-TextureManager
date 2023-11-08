#pragma once

#include "Game.hpp"
#include <unordered_map>

namespace TextureManager
{
    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& key, const char* path);
    SDL_Texture* GetTexture(const std::string& key);
    void CleanUp();
}

#include <iostream>
#include "TextureManager.hpp"

namespace TextureManager
{
    std::unordered_map<std::string, SDL_Texture*> textures;

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& key, const char* path)
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path);

        if (!texture)
        {
            std::cerr << "[!] SDL2 texture failed to load: " << IMG_GetError() << std::endl;
            SDL_Quit();
            return nullptr;
        }

        textures[key] = texture; // Assign the texture to the associated key
        std::cout << "[+] SDL2 texture loaded: \"" << path << "\"" << std::endl;
        return texture;
    }

    SDL_Texture* GetTexture(const std::string& key)
    {
        auto it = textures.find(key);

        if (it != textures.end()) // Check if the iterator finds the key and if it does return the texture
            return it->second;

        return nullptr;
    }

    void CleanUp()
    {
        for (auto& pair : textures)
            SDL_DestroyTexture(pair.second);
            
        textures.clear();
        std::cout << "[+] SDL2 textures cleanup finished" << std::endl;
    }
}

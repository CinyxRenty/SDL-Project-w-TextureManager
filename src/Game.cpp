#include <filesystem>
#include "Game.hpp"
#include "TextureManager.hpp"

namespace Game
{
    bool keepLooping = true;
    const char* windowTitle = "Game";
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool Init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "[!] SDL2 initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }
        std::cout << "[+] SDL2 initialized" << std::endl;
        return true;
    }

    bool InitSubsystems()
    {
        bool imgInit = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
        bool ttfInit = TTF_Init() == 0;
        bool mixerInit = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1;

        // Display specific error if subsystem failed to initialize
        if (!imgInit)
            std::cout << "[!] SDL2 image init failed: " << IMG_GetError() << std::endl;

        if (!ttfInit)
            std::cout << "[!] SDL2 TTF init failed: " << TTF_GetError() << std::endl;

        if (!mixerInit)
            std::cout << "[!] SDL2 mixer init failed: " << Mix_GetError() << std::endl;

        // Display general error that the subsystem initialization failed and return false
        if (!imgInit || !ttfInit || !mixerInit)
        {
            std::cout << "[!] SDL2 subsystems initialization failed" << std::endl;
            return false;
        }
        std::cout << "[+] SDL2 image initialized" << std::endl;
        std::cout << "[+] SDL2 TTF initialized" << std::endl;
        std::cout << "[+] SDL2 mixer initialized" << std::endl;
        std::cout << "[+] SDL2 subsystems initialized" << std::endl;

        return true;
    }

    void CleanUp()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        std::cout << "[+] SDL2 cleanup finished" << std::endl;
    }

    void CreateWindow()
    {
        window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cout << "[!] SDL2 window error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
        std::cout << "[+] SDL2 window created" << std::endl;
    }

    void CreateRenderer()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!renderer)
        {
            std::cout << "[!] SDL2 renderer error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
        std::cout << "[+] SDL2 renderer created" << std::endl;
    }

    void LoadTextures()
    {
        try
        {
            const std::string assets = "assets/";

            if (!std::filesystem::is_directory(assets))
                throw std::runtime_error("assets directory does not exist");

            for (const auto& entry : std::filesystem::directory_iterator(assets))
            {
                if (!entry.is_regular_file() || entry.path().extension() != ".png")
                    continue;

                const std::string key = entry.path().stem().string();
                const std::string fileName = entry.path().filename().string();
                const std::string filePath = assets + fileName;

                if (!TextureManager::LoadTexture(renderer, key, filePath.c_str()))
                    throw std::runtime_error("failed to load texture: " + filePath);
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "[!] SDL2 error: " << e.what() << std::endl;
            TextureManager::CleanUp();
            CleanUp();
        }
    }

    void Render()
    {
        SDL_SetRenderDrawColor(renderer, 21, 20, 249, 255);
        SDL_RenderClear(renderer);
        SDL_RenderSetLogicalSize(renderer, 320, 240); // Scale up textures to window size

        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = 107;
        srcRect.h = 137;

        // Texture destination rect
        SDL_Rect rect;
        rect.x = 70;
        rect.y = 20;
        rect.w = 107;
        rect.h = 137;

        SDL_RenderCopy(renderer, TextureManager::GetTexture("girlIdle"), &srcRect, &rect); // Load texture and store in gpu VRAM

        // Swap buffer
        SDL_RenderPresent(renderer);
    }

    void GameLoop()
    {
        while (keepLooping)
        {
            Render();

            // Ticks = milliseconds since start of sdl init
            if (SDL_GetTicks() > 5000)
                keepLooping = false;
        }
        TextureManager::CleanUp();
        CleanUp();
    }
}

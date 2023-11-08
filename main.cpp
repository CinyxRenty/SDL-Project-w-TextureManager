#include "src/Game.hpp"

int main(int argc, char* argv[])
{
    if (Game::Init() && Game::InitSubsystems())
    {
        Game::CreateWindow();
        Game::CreateRenderer();
        Game::LoadTextures();
        Game::GameLoop();
    }

    return 0;
}

#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include "engine.h"
#include "level_2048.h"

using namespace std;

Engine::Engine() {}

void Engine::run()
{
    Game2048 *game = new Game2048();
    game->startGame();
    delete game;
}

int main()
{
    Engine engine;
    engine.run();
    return 0;
}
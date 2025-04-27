#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include "engine.h"
#include "level_2048.h"
#include "level_Sokoban.h"
#include "level_Snake.h"

using namespace std;

Engine::Engine() {}

void Engine::run2048()
{
    Game2048 *game = new Game2048();
    game->startGame();
    delete game;
}

void Engine::runSokoban()
{
    GameSokoban *game = new GameSokoban();
    game->startGame();
    delete game;
}

void Engine::runSnake()
{
    GameSnake *game = new GameSnake();
    game->startGame();
    delete game;
}

int main()
{
    Engine *engine = new Engine();
    while (true)
    {
        int n;
        cout << "Select a game to play:" << endl;
        cout << "1. 2048" << endl;
        cout << "2. Sokoban" << endl;
        cout << "3. Snake" << endl;
        cout << "0. Exit" << endl;
        cin >> n;
        if (n == 0)
        {
            break;
        }

        switch (n)
        {
        case 1:
            engine->run2048();
            break;
        case 2:
            engine->runSokoban();
            break;
        case 3:
            engine->runSnake();
            break;
        default:
            break;
        }
    }
    return 0;
}
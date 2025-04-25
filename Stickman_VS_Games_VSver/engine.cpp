// engine.cpp

#include <memory>
#include <vector>
#include <iostream>
#include "engine.h"
#include "level_2048.h"
// ...

using namespace std;

Engine::Engine() {}

void Engine::init()
{
    bool fk = true;
}

void Engine::display(const vector<vector<int>> &grid, int size)
{
    system("cls");

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (grid[i][j] != 0)
                cout << setw(6) << grid[i][j];
            else
                cout << setw(6) << ".";
        }
        cout << "\n\n";
    }
}

void Engine::run()
{
    Game2048 *game = new Game2048();

    game->initGame();
    display(game->getGrid(), 4);
    while (true)
    {
        char input = _getch();
        if (input == 'q')
            break;
        game->update(input);
        display(game->getGrid(), 4);
    }
}

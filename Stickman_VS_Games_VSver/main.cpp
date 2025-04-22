// main.cpp is the entry point of the game.

#include "engine.h"

int main()
{
    Engine gameEngine;
    gameEngine.init();
    gameEngine.run();
    gameEngine.shutdown();
    return 0;
}
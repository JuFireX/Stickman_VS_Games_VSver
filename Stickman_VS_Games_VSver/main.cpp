// main.cpp is the entry point of the game. 

#include "engine.h"
#include "level_2048.h"

extern "C" __declspec(dllexport) void startGame2048()
{
    Game2048 game;
    game.startGame();
}

int main() {
    //Engine gameEngine;
    //gameEngine.init();
    //gameEngine.run();
    //gameEngine.shutdown();
    startGame2048();
    return 0;
}
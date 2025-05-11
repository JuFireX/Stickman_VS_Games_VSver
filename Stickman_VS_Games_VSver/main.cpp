#include "engine.h"
#include<iostream>
int main()
{
    Engine* engine = new Engine();

    engine->runGameSnake();
    engine->runGame2048();
    engine->runGameSokoban();
    delete engine;

    std::cout << LEVEL_2048 ;
    return 0;
}

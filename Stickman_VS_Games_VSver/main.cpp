#include "engine.h"
#include<iostream>
int main()
{
    Engine* engine = new Engine();

    //engine->runGameSnake();
    //engine->runGame2048();
    //engine->runGameSokoban();
	//engine->runGameTetris();
    engine->runGamePacman();
    delete engine;

    return 0;
}

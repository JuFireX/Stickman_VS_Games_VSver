#include "engine.h"
#include<iostream>
int main()
{
    Engine* engine = new Engine();
    
    engine->runGame();

    delete engine;
    std::cout << LEVEL_2048 ;
    return 0;
}

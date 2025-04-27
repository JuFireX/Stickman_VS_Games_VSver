#include "engine.h"

int main()
{
    Engine* engine = new Engine();
    engine->init();
    engine->run();
    delete engine;
    return 0;
}

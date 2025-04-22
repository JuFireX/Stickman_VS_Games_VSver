#include "engine.h"
#include "level_2048.h"

int main()
{
    startGame(LEVEL_2048); // 启动2048游戏
    Engine engine;
    engine.init();
    engine.run();
    engine.shutdown();
    return 0;
}

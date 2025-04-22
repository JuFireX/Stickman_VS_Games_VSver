// engine.cpp 定义游戏的输入输出系统
// 包括游戏主循环和渲染系统

#include <memory>
#include "engine.h"
#include "level_2048.h"
#include "level_Mario.h"
#include "level_Pacman.h"
#include "level_Snake.h"
#include "level_Sokoban.h"
#include "level_Tetris.h"

enum Level
{
    LEVEL_2048,
    LEVEL_MARIO,
    LEVEL_PACMAN,
    LEVEL_SNAKE,
    LEVEL_SOKOBAN,
    LEVEL_TETRIS,
};

extern "C" __declspec(dllexport) void startGame(Level level)
{
    switch (level)
    {
    case LEVEL_2048:
        game = std::make_unique<Game2048>();
        game->init();
        break;
    case LEVEL_MARIO:
        game = std::make_unique<GameMario>();
        game->init();
        break;
    case LEVEL_PACMAN:
        game = std::make_unique<GamePacman>();
        game->init();
        break;
    case LEVEL_SNAKE:
        game = std::make_unique<GameSnake>();
        game->init();
        break;
    case LEVEL_SOKOBAN:
        game = std::make_unique<GameSokoban>();
        game->init();
        break;
    case LEVEL_TETRIS:
        game = std::make_unique<GameTetris>();
        game->init();
        break;
    }
}

std::unique_ptr<Game> game;

void Engine::init()
{
    // 初始化游戏窗口和图形资源
    // 假设我们已经有一个初始化窗口的函数 initWindow()
    initWindow();
}

void Engine::run()
{
    // 游戏主循环
    bool running = true;
    while (running)
    {
        // 处理输入事件
        char key = getKeyPress(); // 假设我们有一个获取按键输入的函数 getKeyPress()
        if (key == 'q')
        { // 如果按下 'q' 键，退出游戏
            running = false;
        }
        else if (game)
        {
            game->update(key);
        }

        // 更新游戏状态
        if (game && game->state() == GameState::GameOver)
        {
            running = false;
        }

        // 渲染游戏画面
        renderGame(); // 假设我们有一个渲染游戏画面的函数 renderGame()
    }
}

void Engine::shutdown()
{
    // 释放所有游戏资源
    game.reset();
    shutdownWindow(); // 假设我们有一个关闭窗口的函数 shutdownWindow()
}

void initWindow()
{
    // 初始化窗口代码
}

void shutdownWindow()
{
    // 关闭窗口代码
}

char getKeyPress()
{
    // 获取按键输入的代码
    return 'a'; // 示例返回值
}

void renderGame()
{
    // 渲染游戏画面代码
}
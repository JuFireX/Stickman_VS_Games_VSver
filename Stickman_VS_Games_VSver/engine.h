// engine.h
#ifndef ENGINE_H
#define ENGINE_H
#include <vector>

enum class GameState
{
    Running,
    GameOver
};

class Game
{
public:
    virtual void init() = 0;
    virtual void update(char key) = 0;
    virtual GameState state() const = 0;
    virtual std::vector<std::vector<int>> matrix() const = 0;
    virtual int getScore() const = 0;
    virtual ~Game() {}
};

class Engine
{
public:
    void init();
    void run();
    void shutdown();

    // 游戏引擎核心功能接口
};
#endif // ENGINE_H
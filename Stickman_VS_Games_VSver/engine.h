// engine.h
#ifndef ENGINE_H
#define ENGINE_H
#include <vector>

using namespace std;

enum Level
{
    LEVEL_2048,
    LEVEL_MARIO,
    LEVEL_PACMAN,
    LEVEL_SNAKE,
    LEVEL_SOKOBAN,
    LEVEL_TETRIS,
};

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class GameState
{
    Running,
    GameOver
};

class Game
{
public:
    virtual void initGame() = 0;
    virtual void startGame() = 0;
    virtual void update(char key) = 0;
    virtual GameState state() const = 0;
    virtual vector<vector<int>> getGrid() const = 0;
    virtual int getScore() const = 0;
    virtual ~Game() {}
};

class Engine
{
private:
    void display(const vector<vector<int>>& grid,int size);
public:
    Engine();
    void init();
    void run();

    // 游戏引擎核心功能接口
};
#endif // ENGINE_H
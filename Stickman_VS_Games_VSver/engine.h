// engine.h
#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include <graphics.h>
#include<map>
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

typedef struct position
{
    int val;
    int x;
    int y;
} position;


class Game
{
public:
    virtual void initGame() = 0;
    virtual void startGame() = 0;
    virtual void update(char key) = 0;
    virtual GameState state() const = 0;
    virtual vector<vector<int>> getGrid() const = 0;
    virtual int getScore() const = 0;

    bool gameOver = false;
    virtual void load() = 0; // 加载游戏素材
    map<int, IMAGE> MapImg;
    virtual vector<vector<position>> getMap() const=0;
    int GameHigh = 0;
    int GridSize = 0;
    int GameFrame = 0; // 游戏刷新率
    virtual ~Game() {}
};

class Engine
{
private:
    IMAGE MapImg[200];

    int width = 720, height = 480;
    int MapSizeX = 20, MapSizeY = 12;
    void draw();
    void drawGameMap();
    void loadpicture();
    bool running = true;
    ExMessage msg = ExMessage();

public:
    Engine();
    void init();
    void run();
    // 游戏引擎核心功能接口

    
    std::vector<vector<position>> GameMap;

    void MessageHandle();

    void close();

    void runGame2048();
    Level level = LEVEL_2048; // 默认游戏等级 
    // 根据需要选择不同的游戏类
};
#endif // ENGINE_H
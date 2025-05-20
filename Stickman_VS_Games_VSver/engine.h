// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <graphics.h>
#include <map>
#include <string>
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
	virtual void load() = 0;
	map<int, IMAGE> MapImg;
	virtual vector<vector<position>> getMap() const = 0;
	int GameHigh = 0;
	int GridSize = 0;
	int GameFrame = 0;
	virtual ~Game() {}
};

class Engine
{
private:
	IMAGE MapImg[200];
	int width = 720, height = 480;
	int MapSizeX = 20, MapSizeY = 12;
	bool running = true;
	ExMessage msg = ExMessage();
	inline void putimage_alpha(int x, int y, IMAGE* img, int alpha);

public:
	Engine();
	vector<vector<position>> GameMap;
	void initGame();
	void runGame2048();
	void runGameSnake();
	void runGameSokoban();
	void runGameTetris();
	void runGamePacman();
	void FadeOutWHITE(int width, int height, int speed, int timeout);
	void FadeOutBLACK(int width, int height, int speed, int timeout);
	void FadeInWHITE(int width, int height, int speed, int timeout);
	void FadeInBLACK(int width, int height, int speed, int timeout);
};
#endif
// ENGINE_H
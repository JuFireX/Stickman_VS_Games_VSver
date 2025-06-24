#include "level_Sokoban_II.h"
#include <iostream>
#include <windows.h>

GameSokobanII::GameSokobanII() {}

// Private methods

void GameSokobanII::initLevel()
{
	// 根据关卡设置内部墙、箱子和目标
	if (level == 1)
	{
		int map[10][10] = {
			{EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,EMPTY},
			{EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY},
			{EMPTY,EMPTY,WALL,WALL,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY},
			{EMPTY,EMPTY,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY},
			{WALL,WALL,WALL,EMPTY,WALL,WALL,EMPTY,WALL,WALL,WALL},
			{WALL,TARGET,EMPTY,TARGET,TARGET,BOX,BOX,EMPTY,EMPTY,WALL},
			{WALL,TARGET,BOX,EMPTY,WALL,EMPTY,EMPTY,EMPTY,EMPTY,WALL},
			{WALL,EMPTY,BOX,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL},
			{WALL,EMPTY,BOX,TARGET,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
			{WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY}
		};
		// 初始化网格
		for (int i = 0; i < GRID_SIZE; ++i)
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				grid[i][j] = map[i][j];
			}
		}

		// 设置玩家初始位置
		playerX = 8;
		playerY = 6;
		grid[playerY][playerX] = PLAYER;
	}

	// 计算箱子和目标的数量
	boxCount = 0;
	targetCount = 0;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (grid[i][j] == BOX)
				boxCount++;
			else if (grid[i][j] == TARGET)
				targetCount++;
		}
	}
}

bool GameSokobanII::movePlayer(Direction dir)
{
	int newX = playerX;
	int newY = playerY;

	// 计算新位置
	switch (dir)
	{
	case Direction::LEFT:
		newX--;
		break;
	case Direction::RIGHT:
		newX++;
		break;
	case Direction::UP:
		newY--;
		break;
	case Direction::DOWN:
		newY++;
		break;
	}

	// 检查新位置是否有效
	if (grid[newY][newX] == WALL)
		return false;

	// 如果新位置是箱子,检查是否可以推动
	if (grid[newY][newX] == BOX || grid[newY][newX] == BOX_ON_TARGET)
	{
		int boxNewX = newX + (newX - playerX);
		int boxNewY = newY + (newY - playerY);

		// 检查箱子新位置是否有效
		if (grid[boxNewY][boxNewX] == WALL || grid[boxNewY][boxNewX] == BOX || grid[boxNewY][boxNewX] == BOX_ON_TARGET)
			return false;

		// 移动箱子
		if (grid[boxNewY][boxNewX] == TARGET)
			grid[boxNewY][boxNewX] = BOX_ON_TARGET;
		else
			grid[boxNewY][boxNewX] = BOX;

		// 更新原箱子位置
		if (grid[newY][newX] == BOX_ON_TARGET)
			grid[newY][newX] = TARGET;
		else
			grid[newY][newX] = EMPTY;
	}

	// 移动玩家
	if (grid[playerY][playerX] == PLAYER)
		grid[playerY][playerX] = EMPTY;

	playerX = newX;
	playerY = newY;
	bool needFreshTarget = false;

	if (grid[playerY][playerX] == TARGET)
	{
		grid[playerY][playerX] = PLAYER; // 玩家站在目标上
		needFreshTarget = true;
	}
	else
	{
		grid[playerY][playerX] = PLAYER;
		if (needFreshTarget)
		{
			for (int i = 0; i < GRID_SIZE; ++i) // 还原目标
			{
				for (int j = 0; j < GRID_SIZE; ++j)
				{
					if (grid[i][j] == TARGET)
						grid[i][j] = TARGET;
					if (grid[i][j] != BOX_ON_TARGET)
						grid[i][j] = BOX_ON_TARGET;
				}
			}
			needFreshTarget = false;
		}
	}

	// 检查是否完成关卡
	checkWinCondition();

	return true;
}

void GameSokobanII::checkWinCondition()
{
	int boxesOnTarget = 0;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (grid[i][j] == BOX_ON_TARGET)
				boxesOnTarget++;
		}
	}

	if (boxesOnTarget == targetCount && targetCount > 0)
	{
		gameWon = true;
		gameOver = true;
	}
}

bool GameSokobanII::processInput(char input)
{
	bool validMove = false;

	switch (input)
	{
	case 'a':
		validMove = movePlayer(Direction::LEFT);
		break;
	case 'd':
		validMove = movePlayer(Direction::RIGHT);
		break;
	case 'w':
		validMove = movePlayer(Direction::UP);
		break;
	case 's':
		validMove = movePlayer(Direction::DOWN);
		break;
	case 'r': // 重置关卡
		initLevel();
		validMove = true;
		break;
	}
	return validMove;
}

// Public methods

void GameSokobanII::initGame()
{
	level = 1;
	gameOver = false;
	gameWon = false;
	initLevel();
}

void GameSokobanII::update(char key)
{
	processInput(key);
	if (grid[5][1] != PLAYER && grid[5][1] != BOX && grid[5][1] != BOX_ON_TARGET)
		grid[5][1] = TARGET;
	if (grid[6][1] != PLAYER && grid[6][1] != BOX && grid[6][1] != BOX_ON_TARGET)
		grid[6][1] = TARGET;
	if (grid[5][3] != PLAYER && grid[5][3] != BOX && grid[5][3] != BOX_ON_TARGET)
		grid[5][3] = TARGET;
	if (grid[5][4] != PLAYER && grid[5][4] != BOX && grid[5][4] != BOX_ON_TARGET)
		grid[5][4] = TARGET;
	if (grid[8][3] != PLAYER && grid[8][3] != BOX && grid[8][3] != BOX_ON_TARGET)
		grid[8][3] = TARGET;
}
GameState GameSokobanII::state() const
{
	return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> GameSokobanII::getGrid() const
{
	vector<vector<int>> gridCopy(GRID_SIZE, vector<int>(GRID_SIZE));
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			gridCopy[i][j] = grid[i][j];
		}
	}
	return gridCopy;
}

int GameSokobanII::getScore() const
{
	return level;
}

// Test methods
void GameSokobanII::display(const vector<vector<int>>& grid, int size) const
{
	system("cls");

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (grid[i][j] == EMPTY)
				cout << "  ";
			else if (grid[i][j] == WALL)
				cout << "# ";
			else if (grid[i][j] == PLAYER)
				cout << "@ ";
			else if (grid[i][j] == BOX)
				cout << "B ";
			else if (grid[i][j] == BOX_ON_TARGET)
				cout << "X ";
			else if (grid[i][j] == TARGET)
				cout << "T ";
			else
				cout << "  ";
		}
		cout << "\n";
	}
}

void GameSokobanII::startGame()
{
	initGame();
	display(getGrid(), 10);

	while (!gameOver)
	{
		if (_kbhit())
		{
			char input = _getch();
			if (input == 'q')
				break;
			update(input);
			display(getGrid(), 10);
		}
		// 非自更新
	}
}

// 目测要加三个函数（以下部分与主逻辑无关）
void GameSokobanII::load()
{
	loadimage(&img_Sokoban[0], _T("./PictureResource/GameSokoban/wall.png"), img_size, img_size, true);
	loadimage(&img_Sokoban[1], _T("./PictureResource/GameSokoban/box.jpg"), img_size, img_size, true);
	loadimage(&img_Sokoban[2], _T("./PictureResource/GameSokoban/player.png"), img_size, img_size, true);
	loadimage(&img_Sokoban[3], _T("./PictureResource/GameSokoban/target.png"), img_size, img_size, true);
	loadimage(&img_Sokoban[4], _T("./PictureResource/GameSokoban/target_on_boa .png"), img_size, img_size, true);
	MapImg[WALL] = img_Sokoban[0];
	MapImg[BOX] = img_Sokoban[1];
	MapImg[PLAYER] = img_Sokoban[2];
	MapImg[TARGET] = img_Sokoban[3];
	MapImg[BOX_ON_TARGET] = img_Sokoban[4];
}

vector<vector<position>> GameSokobanII::getMap() const // 重绘地图
{
	vector<vector<int>> state = getGrid();
	vector<vector<position>> GameMap;
	int sizeY = 480 / 12;
	int sizeX = 720 / 18;
	for (int i = 0; i < 12; i++)
	{
		vector<position> row;
		for (int j = 0; j < 18; j++)
		{
			row.push_back({ 0, j * sizeX, i * sizeY });
		}
		GameMap.push_back(row);
	}
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (state[i][j] != EMPTY)
			{
				GameMap[1 + i][4 + j].val = state[i][j];
			}
		}
	}
	return GameMap;
}
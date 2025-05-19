#include "level_2048.h"
#include <iostream>
#include <windows.h>

Game2048::Game2048() : rng(time(nullptr)) {}

// Private methods

bool Game2048::canMoveHorizontal(bool left) const
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = left ? 0 : GRID_SIZE - 1;
			left ? (j < GRID_SIZE - 1) : (j > 0);
			j += left ? 1 : -1)
		{
			if ((grid[i][j] == grid[i][j + (left ? 1 : -1)] && grid[i][j] != 0) ||
				(grid[i][j] == 0 && grid[i][j + (left ? 1 : -1)] != 0))
			{
				return true;
			}
		}
	}
	return false;
}

bool Game2048::canMoveVertical(bool up) const
{
	for (int j = 0; j < GRID_SIZE; ++j)
	{
		for (int i = up ? 0 : GRID_SIZE - 1;
			up ? (i < GRID_SIZE - 1) : (i > 0);
			i += up ? 1 : -1)
		{
			if ((grid[i][j] == grid[i + (up ? 1 : -1)][j] && grid[i][j] != 0) ||
				(grid[i][j] == 0 && grid[i + (up ? 1 : -1)][j] != 0))
			{
				return true;
			}
		}
	}
	return false;
}

bool Game2048::canMove(Direction dir) const
{
	switch (dir)
	{
	case Direction::LEFT:
		return canMoveHorizontal(true);
	case Direction::RIGHT:
		return canMoveHorizontal(false);
	case Direction::UP:
		return canMoveVertical(true);
	case Direction::DOWN:
		return canMoveVertical(false);
	default:
		return false;
	}
}

void Game2048::moveAndMerge(Direction dir)
{
	bool isVertical = (dir == Direction::UP || dir == Direction::DOWN);
	bool isReverse = (dir == Direction::RIGHT || dir == Direction::DOWN);

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		vector<int> line;
		// 提取一行或一列
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			int value = isVertical ? grid[j][i] : grid[i][j];
			if (value != 0)
				line.push_back(value);
		}

		if (isReverse)
			reverse(line.begin(), line.end());

		// 合并相同数字
		vector<int> merged;
		for (size_t j = 0; j < line.size(); ++j)
		{
			if (j + 1 < line.size() && line[j] == line[j + 1])
			{
				merged.push_back(line[j] * 2);
				score += line[j] * 2;
				++j;
			}
			else
			{
				merged.push_back(line[j]);
			}
		}

		// 填充剩余空间
		while (merged.size() < GRID_SIZE)
			merged.push_back(0);
		if (isReverse)
			reverse(merged.begin(), merged.end());

		// 更新网格
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (isVertical)
			{
				grid[j][i] = merged[j];
			}
			else
			{
				grid[i][j] = merged[j];
			}
		}
	}
}

void Game2048::generateNewTile()
{
	vector<Position> emptyPositions;
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (grid[i][j] == 0)
			{
				emptyPositions.push_back({ i, j });
			}
		}
	}

	if (!emptyPositions.empty())
	{
		uniform_int_distribution<int> positionDist(0, (int)emptyPositions.size() - 1);
		uniform_int_distribution<int> valueDist(0, 9);

		Position pos = emptyPositions[positionDist(rng)];
		grid[pos.row][pos.col] = (valueDist(rng) < 9) ? 2 : 4;
	}
}

bool Game2048::isGameOver() const
{
	return !canMove(Direction::LEFT) &&
		!canMove(Direction::RIGHT) &&
		!canMove(Direction::UP) &&
		!canMove(Direction::DOWN);
}

bool Game2048::processInput(char key)
{
	if (gameOver)
		return false;

	Direction dir;
	switch (key)
	{
	case 'a':
		dir = Direction::LEFT;
		break;
	case 'd':
		dir = Direction::RIGHT;
		break;
	case 'w':
		dir = Direction::UP;
		break;
	case 's':
		dir = Direction::DOWN;
		break;
	default:
		return false;
	}

	if (canMove(dir))
	{
		moveAndMerge(dir);
		generateNewTile();
		gameOver = isGameOver();
		return true;
	}
	return false;
}

// Public methods

void Game2048::initGame()
{
	score = 0;
	gameOver = false;
	memset(grid, 0, sizeof(grid));
	generateNewTile();
	generateNewTile();
}

void Game2048::update(char key)
{
	processInput(key);
}

GameState Game2048::state() const
{
	return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> Game2048::getGrid() const
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

int Game2048::getScore() const
{
	return score;
}

// Test methods

void Game2048::display(const vector<vector<int>>& grid, int size) const
{
	system("cls");

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (grid[i][j] != 0)
				cout << setw(6) << grid[i][j];
			else
				cout << setw(6) << ".";
		}
		cout << "\n\n";
	}
}

void Game2048::startGame()
{
	initGame();
	display(getGrid(), 4);

	while (!gameOver)
	{
		if (_kbhit())
		{
			char input = _getch();
			if (input == 'q')
				break;
			update(input);
			display(getGrid(), 4);
		}
		// 非自更新
	}
}

void Game2048::load()
{
	loadimage(&img_2048[0], _T("./PictureResource/Game2048/0.png"), img_size, img_size, true);
	loadimage(&img_2048[1], _T("./PictureResource/Game2048/2.png"), img_size, img_size, true);
	loadimage(&img_2048[2], _T("./PictureResource/Game2048/4.png"), img_size, img_size, true);
	loadimage(&img_2048[3], _T("./PictureResource/Game2048/8.png"), img_size, img_size, true);
	loadimage(&img_2048[4], _T("./PictureResource/Game2048/16.png"), img_size, img_size, true);
	loadimage(&img_2048[5], _T("./PictureResource/Game2048/32.png"), img_size, img_size, true);
	loadimage(&img_2048[6], _T("./PictureResource/Game2048/64.png"), img_size, img_size, true);
	loadimage(&img_2048[7], _T("./PictureResource/Game2048/128.png"), img_size, img_size, true);
	loadimage(&img_2048[8], _T("./PictureResource/Game2048/256.png"), img_size, img_size, true);
	loadimage(&img_2048[9], _T("./PictureResource/Game2048/512.png"), img_size, img_size, true);
	loadimage(&img_2048[10], _T("./PictureResource/Game2048/1024.png"), img_size, img_size, true);
	loadimage(&img_2048[11], _T("./PictureResource/Game2048/2048.png"), img_size, img_size, true);
	MapImg[0] = img_2048[0];
	MapImg[2] = img_2048[1];
	MapImg[4] = img_2048[2];
	MapImg[8] = img_2048[3];
	MapImg[16] = img_2048[4];
	MapImg[32] = img_2048[5];
	MapImg[64] = img_2048[6];
	MapImg[128] = img_2048[7];
	MapImg[256] = img_2048[8];
	MapImg[512] = img_2048[9];
	MapImg[1024] = img_2048[10];
	MapImg[2048] = img_2048[11];
}

vector<vector<position>> Game2048::getMap() const
{
	vector<vector<int>> state = getGrid();
	vector<vector<position>> GameMap;
	int sizeY = 480 / 24;
	int sizeX = 720 / 36;
	for (int i = 0; i < 24; i++)
	{
		vector<position> row;
		for (int j = 0; j < 36; j++)
		{
			row.push_back({ -1, j * sizeX, i * sizeY });
		}
		GameMap.push_back(row);
	}
	GameMap[4][8].val = state[0][0];
	GameMap[4][12].val = state[0][1];
	GameMap[4][16].val = state[0][2];
	GameMap[4][20].val = state[0][3];
	GameMap[8][8].val = state[1][0];
	GameMap[8][12].val = state[1][1];
	GameMap[8][16].val = state[1][2];
	GameMap[8][20].val = state[1][3];
	GameMap[12][8].val = state[2][0];
	GameMap[12][12].val = state[2][1];
	GameMap[12][16].val = state[2][2];
	GameMap[12][20].val = state[2][3];
	GameMap[16][8].val = state[3][0];
	GameMap[16][12].val = state[3][1];
	GameMap[16][16].val = state[3][2];
	GameMap[16][20].val = state[3][3];
	return GameMap;
}

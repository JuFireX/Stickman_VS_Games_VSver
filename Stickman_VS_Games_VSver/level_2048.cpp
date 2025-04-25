#include "level_2048.h"
#include <windows.h>

Game2048::Game2048() : rng(time(nullptr)) {}

// private methods

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
				emptyPositions.push_back({i, j});
			}
		}
	}

	if (!emptyPositions.empty())
	{
		uniform_int_distribution<int> positionDist(0, emptyPositions.size() - 1);
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

// public methods

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
	bool moved = processInput(key);
}

GameState Game2048::state() const
{
	return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> Game2048::getGrid() const
{
	vector<vector<int>> state(GRID_SIZE, vector<int>(GRID_SIZE));
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			state[i][j] = grid[i][j];
		}
	}
	return state;
}

int Game2048::getScore() const
{
	return score;
}

// test methods

void Game2048::startGame()
{
	initGame();
	update('0');
	while (true)
	{
		char input = _getch();
		if (input == 'q')
			break;
		if (processInput(input))
			update(input);
	}
}

/*
void Engine::run()
{
	Game2048 *game = new Game2048();

	game->initGame();
	display(game->getGrid(), 4);
	while (true)
	{
		char input = _getch();
		if (input == 'q')
			break;
		game->update(input);
		display(game->getGrid(), 4);
	}
}
*/
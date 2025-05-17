#include <windows.h>
#include <iostream>
#include "level_Snake.h"

GameSnake::GameSnake() : rng(time(nullptr))
{
}

// Private methods

void GameSnake::initGrid()
{
	// 初始化网格为空
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1)
				grid[i][j] = WALL; // 边界墙
			else
				grid[i][j] = EMPTY;
		}
	}
}

void GameSnake::initSnake()
{
	// 清空蛇
	snake.clear();

	// 初始蛇位置（中心位置）
	int centerX = GRID_SIZE / 2;
	int centerY = GRID_SIZE / 2;

	// 添加蛇头和两个身体部分
	snake.push_back({centerY, centerX});
	snake.push_back({centerY, centerX - 1});
	snake.push_back({centerY, centerX - 2});
}

void GameSnake::generateFood()
{
	uniform_int_distribution<int> dist(1, GRID_SIZE - 2); // 避开边界墙

	while (true)
	{
		int x = dist(rng);
		int y = dist(rng);

		// 确保食物不会生成在蛇身上
		bool onSnake = false;
		for (const auto &segment : snake)
		{
			if (segment.first == y && segment.second == x)
			{
				onSnake = true;
				break;
			}
		}

		if (!onSnake)
		{
			food = {y, x};
			break;
		}
	}
}

void GameSnake::updateGrid()
{
	// 清空网格（保留边界墙）
	for (int i = 1; i < GRID_SIZE - 1; ++i)
	{
		for (int j = 1; j < GRID_SIZE - 1; ++j)
		{
			grid[i][j] = EMPTY;
		}
	}

	// 放置食物
	grid[food.first][food.second] = FOOD;

	// 放置蛇身
	for (size_t i = 1; i < snake.size(); ++i)
	{
		grid[snake[i].first][snake[i].second] = SNAKE_BODY;
	}

	// 放置蛇头
	grid[snake[0].first][snake[0].second] = SNAKE_HEAD;
}

bool GameSnake::moveSnake()
{
	// 获取蛇头位置
	int headY = snake[0].first;
	int headX = snake[0].second;

	// 根据方向计算新的头部位置
	switch (direction)
	{
	case Direction::LEFT:
		headX--;
		break;
	case Direction::RIGHT:
		headX++;
		break;
	case Direction::UP:
		headY--;
		break;
	case Direction::DOWN:
		headY++;
		break;
	}

	// 检查碰撞
	if (headX <= 0 || headX >= GRID_SIZE - 1 || headY <= 0 || headY >= GRID_SIZE - 1)
	{
		// 撞墙
		gameOver = true;
		return false;
	}

	// 检查是否撞到自己
	for (size_t i = 0; i < snake.size(); ++i)
	{
		if (snake[i].first == headY && snake[i].second == headX)
		{
			gameOver = true;
			return false;
		}
	}

	// 检查是否吃到食物
	bool ateFood = (headY == food.first && headX == food.second);

	// 移动蛇
	snake.insert(snake.begin(), {headY, headX});
	if (!ateFood)
	{
		// 如果没吃到食物，移除尾部
		snake.pop_back();
	}
	else
	{
		// 吃到食物，增加分数并生成新食物
		score += 10;
		generateFood();
	}

	// 更新网格
	updateGrid();

	return true;
}

bool GameSnake::processInput(char key)
{
	Direction newDir = direction;

	switch (key)
	{
	case 'a':
		newDir = Direction::LEFT;
		break;
	case 'd':
		newDir = Direction::RIGHT;
		break;
	case 'w':
		newDir = Direction::UP;
		break;
	case 's':
		newDir = Direction::DOWN;
		break;
	case ' ':
		break;
	default:
		return false;
	}

	// 防止180度转向（不能直接掉头）
	if ((direction == Direction::LEFT && newDir == Direction::RIGHT) ||
		(direction == Direction::RIGHT && newDir == Direction::LEFT) ||
		(direction == Direction::UP && newDir == Direction::DOWN) ||
		(direction == Direction::DOWN && newDir == Direction::UP))
	{
		return false;
	}

	direction = newDir;
	return true;
}

// Public methods

void GameSnake::initGame()
{
	gameOver = false;
	score = 0;
	initGrid();
	initSnake();
	generateFood();
	updateGrid();
}

void GameSnake::update(char key)
{
	if (processInput(key))
		moveSnake();
}

GameState GameSnake::state() const
{
	return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> GameSnake::getGrid() const
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

int GameSnake::getScore() const
{
	return score;
}

// Test methods
void GameSnake::display(const vector<vector<int>> &grid, int size) const
{
	system("cls");

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j] << ' ';
		}
		cout << "\n";
	}

	cout << "\n使用WASD键移动, ESC退出\n";
	if (gameOver)
		cout << "\n游戏结束!" << "\n ";
}

void GameSnake::startGame()
{
	initGame();
	display(getGrid(), 20);

	while (!gameOver)
	{
		if (_kbhit())
		{
			char input = _getch();
			if (input == 'q')
				break;
			update(input);
			display(getGrid(), 20);
		}
		// 自更新
		else
		{
			update(' ');
			display(getGrid(), 20);
		}
		Sleep(50);
	}
}

// 不准乱动的函数

void GameSnake::load() // 下载图片
{
	loadimage(&img_snake[0], _T("./PictureResource/GameSnake/head.png"), img_size, img_size, true);
	loadimage(&img_snake[1], _T("./PictureResource/GameSnake/body.png"), img_size, img_size, true);
	loadimage(&img_snake[2], _T("./PictureResource/GameSnake/food.png"), img_size, img_size, true);
	loadimage(&img_snake[3], _T("./PictureResource/GameSnake/wall.png"), img_size, img_size, true);
	MapImg[SNAKE_HEAD] = img_snake[0];
	MapImg[SNAKE_BODY] = img_snake[1];
	MapImg[FOOD] = img_snake[2];
	MapImg[WALL] = img_snake[3];
}

vector<vector<position>> GameSnake::getMap() const // 重绘地图
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
			row.push_back({0, j * sizeX, i * sizeY});
		}
		GameMap.push_back(row);
	}
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (state[i][j] != EMPTY)
			{
				GameMap[2 + i][8 + j].val = state[i][j];
			}
		}
	}
	return GameMap;
}

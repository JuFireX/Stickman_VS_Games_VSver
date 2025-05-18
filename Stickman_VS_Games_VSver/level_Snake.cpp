#include <windows.h>
#include <iostream>
#include "level_Snake.h"

GameSnake::GameSnake() : rng(time(nullptr)) {}

// Private methods

void GameSnake::initGrid()
{
	// ��ʼ������Ϊ��
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1)
				grid[i][j] = WALL; // �߽�ǽ
			else
				grid[i][j] = EMPTY;
		}
	}
}

void GameSnake::initSnake()
{
	// �����
	snake.clear();

	// ��ʼ��λ�ã�����λ�ã�
	int centerX = GRID_SIZE / 2;
	int centerY = GRID_SIZE / 2;

	// �����ͷ���������岿��
	snake.push_back({centerY, centerX});
	snake.push_back({centerY, centerX - 1});
	snake.push_back({centerY, centerX - 2});
}

void GameSnake::generateFood()
{
	uniform_int_distribution<int> dist(1, GRID_SIZE - 2); // �ܿ��߽�ǽ

	while (true)
	{
		int x = dist(rng);
		int y = dist(rng);

		// ȷ��ʳ�ﲻ��������������
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
	// ������񣨱����߽�ǽ��
	for (int i = 1; i < GRID_SIZE - 1; ++i)
	{
		for (int j = 1; j < GRID_SIZE - 1; ++j)
		{
			grid[i][j] = EMPTY;
		}
	}

	// ����ʳ��
	grid[food.first][food.second] = FOOD;

	// ��������
	for (size_t i = 1; i < snake.size(); ++i)
	{
		grid[snake[i].first][snake[i].second] = SNAKE_BODY;
	}

	// ������ͷ
	grid[snake[0].first][snake[0].second] = SNAKE_HEAD;
}

bool GameSnake::moveSnake()
{
	// ��ȡ��ͷλ��
	int headY = snake[0].first;
	int headX = snake[0].second;

	// ���ݷ�������µ�ͷ��λ��
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

	// �����ײ
	if (headX <= 0 || headX >= GRID_SIZE - 1 || headY <= 0 || headY >= GRID_SIZE - 1)
	{
		// ײǽ
		gameOver = true;
		return false;
	}

	// ����Ƿ�ײ���Լ�
	for (size_t i = 0; i < snake.size(); ++i)
	{
		if (snake[i].first == headY && snake[i].second == headX)
		{
			gameOver = true;
			return false;
		}
	}

	// ����Ƿ�Ե�ʳ��
	bool ateFood = (headY == food.first && headX == food.second);

	// �ƶ���
	snake.insert(snake.begin(), {headY, headX});
	if (!ateFood)
	{
		// ���û�Ե�ʳ��Ƴ�β��
		snake.pop_back();
	}
	else
	{
		// �Ե�ʳ����ӷ�����������ʳ��
		score += 10;
		generateFood();
	}

	// ��������
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

	// ��ֹ180��ת�򣨲���ֱ�ӵ�ͷ��
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

	cout << "\nʹ��WASD���ƶ�, ESC�˳�\n";
	if (gameOver)
		cout << "\n��Ϸ����!" << "\n ";
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
		// �Ը���
		else
		{
			update(' ');
			display(getGrid(), 20);
		}
		Sleep(50);
	}
}

// ��׼�Ҷ��ĺ���

void GameSnake::load() // ����ͼƬ
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

vector<vector<position>> GameSnake::getMap() const // �ػ��ͼ
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

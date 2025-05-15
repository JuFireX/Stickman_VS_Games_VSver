#include <windows.h>
#include <iostream>
#include "level_Pacman.h"
GamePacman::GamePacman() : rng(time(nullptr))
{
}
void GamePacman::initGrid()
{
	int map[20][20] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0},
					{0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0},
					{0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
					{0,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0},
					{0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0},
					{0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
					{0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0},
					{0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,0},
					{0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0},
					{0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0},
					{0,1,0,1,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,0},
					{0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
					{0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
					{0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0},
					{0,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0},
					{0,1,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
					{0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
					{0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
}
void GamePacman::initMovers()
{
	player.x = 1;
	player.y = 18;
	player.direction = 0;
	player.speed = 3;
	ghost[0].x = 18;
	ghost[0].y = 1;
	ghost[0].direction = 2;
	ghost[0].speed = 2;
	ghost[0].live = 1;
	ghost[1].x = 18;
	ghost[1].y = 16;
	ghost[1].direction = 2;
	ghost[1].speed = 2;
	ghost[1].live = 1;
	ghost[2].x = 1;
	ghost[2].y = 1;
	ghost[2].direction = 0;
	ghost[2].speed = 1;
	ghost[2].form = 0;
	ghost[2].live = 1;
}
bool GamePacman::processInput(char key)
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
	direction = newDir;
	return true;
}
void GamePacman::movePlayer()
{
	int X = player.x;
	int Y = player.y;
	if (key.message == WM_KEYDOWN)
	{
		switch (key.vkcode)
		{
		case 'W':
			if (map[player.y - 1][player.x] != 0)
			{
				player.derection = 1;
				player.x = player.x * 36;
			}
			break;
		case 'A':
			if (map[player.y][player.x - 1] != 0)
			{
				player.derection = 2;
				player.y = player.y * 36;
			}
			break;
		case 'S':
			if (map[player.y + 1][player.x] != 0)
			{
				player.derection = 3;
				player.x = player.x * 36;
			}
			break;
		case 'D':
			if (map[player.y][player.x + 1] != 0)
			{
				player.derection = 0;
				player.y = player.y * 36;
			}
			break;
		}
	}
	switch (player.derection)
	{
	case 0:
		if (map[player.y][player.x / 36 + 1] != 0)
			player.x += player.speed;
		break;
	case 1:
		if (map[player.y / 36][player.x] != 0)
			player.y -= player.speed;
		break;
	case 2:
		if (map[player.y][player.x / 36] != 0)
			player.x -= player.speed;
		break;
	case 3:
		if (map[player.y / 36 + 1][player.x] != 0)
			player.y += player.speed;
		break;
	}
}
//main
void GamePacman::initGame()
{
	gameOver = false;
	score = 0;
	initGrid();
	initSnake();

	updateGrid();
}
// Test methods
void GamePacman::display(const vector<vector<int>>& grid, int size) const
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

void GamePacman::startGame()
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


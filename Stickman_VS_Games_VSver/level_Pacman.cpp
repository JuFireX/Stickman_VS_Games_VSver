#include "level_Pacman.h"
#include <iostream>
#include <windows.h>

GamePacman::GamePacman() : rng((int)time(nullptr)) {}

int GamePacman::ghostDirection(int ghostX, int ghostY, int playerX, int playerY, int* track_x, int* track_y)
{
	int map1[20][20] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
						{0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
						{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
						{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
						{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
						{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
						{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
						{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
						{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
						{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
						{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
						{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
						{0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
						{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
						{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
						{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
						{0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
						{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
	int trace[400][3];
	int k = 0, l = 0, direction = 2;
	trace[k][0] = ghostX;
	trace[k][1] = ghostY;
	trace[k][2] = 0;
	int dx[4] = { 1, -1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };
	int pc = 0, pre = -1;
	map1[ghostY][ghostX] = 2;
	while (trace[k][0] != playerX || trace[k][1] != playerY)
	{
		if (pc == 0)
			pre++;
		if (trace[pre][1] + dy[pc] <= 20 && trace[pre][0] + dx[pc] <= 20 && map1[trace[pre][1] + dy[pc]][trace[pre][0] + dx[pc]] == 1)
		{
			k++;
			trace[k][0] = trace[pre][0] + dx[pc];
			trace[k][1] = trace[pre][1] + dy[pc];
			trace[k][2] = pre;
			map1[trace[pre][1] + dy[pc]][trace[pre][0] + dx[pc]] = 2;
		}
		pc = (pc + 1) % 4;
	}
	*track_x = trace[pre][0];
	*track_y = trace[pre][1];
	while (trace[k][2] != 0)
	{
		k = trace[k][2];
	}
	if ((ghostX) < trace[k][0])
		direction = 0;
	if ((ghostX) > trace[k][0])
		direction = 2;
	if ((ghostY) > trace[k][1])
		direction = 1;
	if ((ghostY) < trace[k][1])
		direction = 3;
	return direction;
}

void GamePacman::initGrid()
{
	int map[GRID_SIZE][GRID_SIZE] = { {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, WALL, FOOD, WALL, FOOD, FOOD, FOOD, WALL, WALL, FOOD, FOOD, FOOD, WALL, FOOD, WALL, FOOD, FOOD, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD},
									 {FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, WALL},
									 {WALL, WALL, FOOD, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, FOOD, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, WALL, WALL, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL} };
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			food_grid[i][j] = map[i][j];
			run_grid[i][j] = map[i][j];
			if (map[i][j] == FOOD)
			{
				run_grid[i][j] = EMPTY;
				target++;
			}
			run_grid_copy[i][j] = run_grid[i][j];
		}
	}
}

void GamePacman::initMovers()
{
	player.x = 6;
	player.y = 18;
	player.old_x = 6;
	player.old_y = 18;
	player.direction = Direction::RIGHT;
	player.speed = 1;
	ghost[0].x = 13;
	ghost[0].y = 18;
	ghost[0].old_x = 13;
	ghost[0].old_y = 18;
	ghost[0].direction = Direction::LEFT;
	ghost[0].speed = 1;
	ghost[0].live = 1;
	ghost[1].x = 2;
	ghost[1].y = 5;
	ghost[1].old_x = 2;
	ghost[1].old_y = 5;
	ghost[1].direction = Direction::LEFT;
	ghost[1].speed = 1;
	ghost[1].live = 1;
	ghost[2].x = 17;
	ghost[2].y = 5;
	ghost[2].old_x = 17;
	ghost[2].old_y = 5;
	ghost[2].direction = Direction::RIGHT;
	ghost[2].speed = 1;
	ghost[2].form = 0;
	ghost[2].live = 1;
}
void GamePacman::initGame()
{
	phase = 1;
	score = 1;
	initGrid();
	initMovers();
	updateGrid();
}
void GamePacman::updateGrid()
{
	if (food_grid[player.old_y][player.old_x] == FOOD)
	{
		food_grid[player.old_y][player.old_x] = EMPTY;
		score += 1;
	}

	//
	run_grid[player.old_y][player.old_x] = EMPTY;
	run_grid[ghost[0].old_y][ghost[0].old_x] = EMPTY;
	run_grid[ghost[1].old_y][ghost[1].old_x] = EMPTY;
	run_grid[ghost[2].old_y][ghost[2].old_x] = EMPTY;

	//
	run_grid[player.y][player.x] = PLAYER;
	run_grid[ghost[0].y][ghost[0].x] = GHOST1;
	run_grid[ghost[1].y][ghost[1].x] = GHOST2;
	run_grid[ghost[2].y][ghost[2].x] = GHOST3;
}

bool GamePacman::processInput(char input)
{
	Direction newDir = player.direction;
	switch (input)
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
	case 'r':
		initGame();
		return true;
	case ' ':
		break;
	default:
		return false;
	}

	bool canChangeDirection = true;
	switch (newDir)
	{
	case Direction::RIGHT:
		if (run_grid[player.y][player.x + 1] == WALL)
			canChangeDirection = false;
		break;
	case Direction::UP:
		if (run_grid[player.y - 1][player.x] == WALL)
			canChangeDirection = false;
		break;
	case Direction::LEFT:
		if (run_grid[player.y][player.x - 1] == WALL)
			canChangeDirection = false;
		break;
	case Direction::DOWN:
		if (run_grid[player.y + 1][player.x] == WALL)
			canChangeDirection = false;
		break;
	}

	if (canChangeDirection)
		player.direction = newDir;

	return true;
}

void GamePacman::movePlayer()
{
	player.old_x = player.x;
	player.old_y = player.y;
	switch (player.direction)
	{
	case Direction::RIGHT:
		if (run_grid[player.y][player.x + 1] != WALL)
			player.x += player.speed;
		break;
	case Direction::UP:
		if (run_grid[player.y - 1][player.x] != WALL)
			player.y -= player.speed;
		break;
	case Direction::LEFT:
		if (run_grid[player.y][player.x - 1] != WALL)
			player.x -= player.speed;
		break;
	case Direction::DOWN:
		if (run_grid[player.y + 1][player.x] != WALL)
			player.y += player.speed;
		break;
	}
	updateGrid();
}

void GamePacman::moveGhosts()
{
	static int moveCounter = 0;

	ghost[0].old_x = ghost[0].x;
	ghost[0].old_y = ghost[0].y;
	ghost[1].old_x = ghost[1].x;
	ghost[1].old_y = ghost[1].y;
	ghost[2].old_x = ghost[2].x;
	ghost[2].old_y = ghost[2].y;

	int track_x, track_y;

	if (moveCounter == 0)
	{
		int dir1 = ghostDirection(ghost[0].x, ghost[0].y, player.x, player.y, &track_x, &track_y);

		switch (dir1)
		{
		case 0:
			if (run_grid[ghost[0].y][ghost[0].x + 1] != WALL)
				ghost[0].x += ghost[0].speed;
			break;
		case 1:
			if (run_grid[ghost[0].y - 1][ghost[0].x] != WALL)
				ghost[0].y -= ghost[0].speed;
			break;
		case 2:
			if (run_grid[ghost[0].y][ghost[0].x - 1] != WALL)
				ghost[0].x -= ghost[0].speed;
			break;
		case 3:
			if (run_grid[ghost[0].y + 1][ghost[0].x] != WALL)
				ghost[0].y += ghost[0].speed;
			break;
		}

		int dir2 = ghostDirection(ghost[1].x, ghost[1].y, player.old_x, player.old_y, &track_x, &track_y);

		switch (dir2)
		{
		case 0:
			if (run_grid[ghost[1].y][ghost[1].x + 1] != WALL)
				ghost[1].x += ghost[1].speed;
			break;
		case 1:
			if (run_grid[ghost[1].y - 1][ghost[1].x] != WALL)
				ghost[1].y -= ghost[1].speed;
			break;
		case 2:
			if (run_grid[ghost[1].y][ghost[1].x - 1] != WALL)
				ghost[1].x -= ghost[1].speed;
			break;
		case 3:
			if (run_grid[ghost[1].y + 1][ghost[1].x] != WALL)
				ghost[1].y += ghost[1].speed;
			break;
		}
		int dir3 = ghostDirection(ghost[2].x, ghost[2].y, player.old_x, player.old_y, &track_x, &track_y);

		switch (dir3)
		{
		case 0:
			if (run_grid[ghost[2].y][ghost[2].x + 1] != WALL)
				ghost[2].x += ghost[2].speed;
			break;
		case 1:
			if (run_grid[ghost[2].y - 1][ghost[2].x] != WALL)
				ghost[2].y -= ghost[2].speed;
			break;
		case 2:
			if (run_grid[ghost[2].y][ghost[2].x - 1] != WALL)
				ghost[2].x -= ghost[2].speed;
			break;
		case 3:
			if (run_grid[ghost[2].y + 1][ghost[2].x] != WALL)
				ghost[2].y += ghost[2].speed;
			break;
		}
	}

	moveCounter = (moveCounter + 1) % 2;
}

void GamePacman::update(char key)
{
	if (processInput(key))
		movePlayer();

	moveGhosts();

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			grid[i][j] = food_grid[i][j];
			if (run_grid[i][j] != EMPTY && run_grid[i][j] != WALL)
			{
				grid[i][j] = run_grid[i][j];
			}
		}
	}
	judgeScore();
	for (int i = 0; i < 3; i++)
	{
		if (player.x == ghost[i].x && player.y == ghost[i].y)
		{
			for (int i = 0; i < GRID_SIZE; ++i)
			{
				for (int j = 0; j < GRID_SIZE; ++j)
				{
					run_grid[i][j] = run_grid_copy[i][j];
				}
			}
			initMovers();
			break;
		}
	}
}

vector<vector<int>> GamePacman::getGrid() const
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

void GamePacman::judgeScore()
{

	if (score >= target)
		gameOver = true;
}

int GamePacman::getScore() const
{
	return score;
}

GameState GamePacman::state() const
{
	return GameState::Running;
}

// Test methods
void GamePacman::display(const vector<vector<int>>& grid, int size) const
{
	system("cls");
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (grid[i][j] == WALL)
				cout << "# ";
			else if (grid[i][j] == FOOD)
				cout << "* ";
			else if (grid[i][j] == PLAYER)
				cout << "@ ";
			else if (grid[i][j] == GHOST1)
				cout << "1 ";
			else if (grid[i][j] == GHOST2)
				cout << "2 ";
			else if (grid[i][j] == GHOST3)
				cout << "3 ";
			else if (grid[i][j] == EMPTY)
				cout << "  ";
			else
				cout << "  ";
		}
		cout << endl;
	}
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

		else
		{
			update(' ');
			display(getGrid(), 20);
		}
		Sleep(1000 / 6);
	}
}

void GamePacman::load()
{
	loadimage(&player_img[0], _T("./PictureResource/GamePacman/RIGHT.png"), img_size, img_size, true);
	loadimage(&player_img[1], _T("./PictureResource/GamePacman/LEFT.png"), img_size, img_size, true);
	loadimage(&player_img[2], _T("./PictureResource/GamePacman/UP.png"), img_size, img_size, true);
	loadimage(&player_img[3], _T("./PictureResource/GamePacman/DOWN.png"), img_size, img_size, true);
	loadimage(&player_img[4], _T("./PictureResource/GamePacman/close.png"), img_size, img_size, true);
	loadimage(&ghost_img[0], _T("./PictureResource/GamePacman/3.png"), img_size, img_size, true);
	loadimage(&ghost_img[1], _T("./PictureResource/GamePacman/4.png"), img_size, img_size, true);
	loadimage(&ghost_img[2], _T("./PictureResource/GamePacman/5.png"), img_size, img_size, true);
	loadimage(&Wall, _T("./PictureResource/GamePacman/wall.png"), img_size, img_size, true);
	loadimage(&Food, _T("./PictureResource/GamePacman/food.png"), 20, 20, true);
	MapImg[WALL] = Wall;
	MapImg[FOOD] = Food;
	MapImg[GHOST1] = ghost_img[0];
	MapImg[GHOST2] = ghost_img[1];
	MapImg[GHOST3] = ghost_img[2];
}

vector<vector<position>> GamePacman::getMap() const
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
				GameMap[2 + i][8 + j].val = state[i][j];
			}
		}
	}
	return GameMap;
}
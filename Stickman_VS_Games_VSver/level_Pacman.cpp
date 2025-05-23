#include "level_Pacman.h"
#include <iostream>
#include <windows.h>
#include <climits> // 添加头文件以使用INT_MAX

GamePacman::GamePacman() : rng((int)time(nullptr)) {}

int GamePacman::ghostDirection(int ghostX, int ghostY, int playerX, int playerY, int* track_x, int* track_y)
{
	// 地图定义 - 使用类成员变量中的地图，避免重复定义
	// 方向数组：右、左、上、下
	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, -1, 1 };
	
	// 使用简化的寻路算法，限制搜索深度和内存使用
	const int MAX_DEPTH = 400; // 增加搜索深度以确保能找到完整路径
	const int MAP_SIZE = 19;
	
	// 使用固定大小的数组代替vector，避免动态内存分配
	struct Node {
		int x, y;
		int g;
		int f;
		int parentX, parentY; // 直接存储父节点坐标，而不是索引
	};
	
	// 使用二维数组记录已访问的节点和它们的信息
	bool visited[MAP_SIZE][MAP_SIZE] = { false };
	bool inOpen[MAP_SIZE][MAP_SIZE] = { false };
	Node nodeInfo[MAP_SIZE][MAP_SIZE] = { 0 };
	
	// 使用简单数组实现优先队列，限制大小
	const int MAX_QUEUE_SIZE = 400; // 足够大的队列大小
	int openX[MAX_QUEUE_SIZE], openY[MAX_QUEUE_SIZE];
	int openCount = 0;
	
	// 初始化起点
	openX[openCount] = ghostX;
	openY[openCount] = ghostY;
	openCount++;
	
	inOpen[ghostY][ghostX] = true;
	nodeInfo[ghostY][ghostX].x = ghostX;
	nodeInfo[ghostY][ghostX].y = ghostY;
	nodeInfo[ghostY][ghostX].g = 0;
	nodeInfo[ghostY][ghostX].f = abs(playerX - ghostX) + abs(playerY - ghostY);
	nodeInfo[ghostY][ghostX].parentX = -1;
	nodeInfo[ghostY][ghostX].parentY = -1;
	
	bool foundPath = false;
	int currentDepth = 0;
	
	// A*主循环 - 不再受深度限制，而是由开放列表是否为空决定
	while (openCount > 0) {
		// 找到f值最小的节点
		int minIdx = 0;
		for (int i = 1; i < openCount; i++) {
			if (nodeInfo[openY[i]][openX[i]].f < nodeInfo[openY[minIdx]][openX[minIdx]].f) {
				minIdx = i;
			}
		}
		
		// 获取当前节点
		int currentX = openX[minIdx];
		int currentY = openY[minIdx];
		
		// 从开放列表中移除
		openX[minIdx] = openX[openCount - 1];
		openY[minIdx] = openY[openCount - 1];
		openCount--;
		inOpen[currentY][currentX] = false;
		
		// 标记为已访问
		visited[currentY][currentX] = true;
		
		// 如果到达目标，结束搜索
		if (currentX == playerX && currentY == playerY) {
			foundPath = true;
			break;
		}
		
		// 检查四个方向的相邻节点
		for (int i = 0; i < 4; i++) {
			int newX = currentX + dx[i];
			int newY = currentY + dy[i];
			
			// 检查边界
			if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE) {
				continue;
			}
			
			// 检查是否是墙或已访问
			if (run_grid[newY][newX] == WALL || visited[newY][newX]) {
				continue;
			}
			
			// 计算新的g值
			int newG = nodeInfo[currentY][currentX].g + 1;
			
			// 如果节点不在开放列表中或找到了更好的路径
			if (!inOpen[newY][newX] || newG < nodeInfo[newY][newX].g) {
				// 更新节点信息
				nodeInfo[newY][newX].g = newG;
				nodeInfo[newY][newX].f = newG + abs(playerX - newX) + abs(playerY - newY);
				nodeInfo[newY][newX].parentX = currentX;
				nodeInfo[newY][newX].parentY = currentY;
				
				// 如果节点不在开放列表中，添加它
				if (!inOpen[newY][newX]) {
					// 检查队列是否已满
					if (openCount < MAX_QUEUE_SIZE) {
						openX[openCount] = newX;
						openY[openCount] = newY;
						openCount++;
						inOpen[newY][newX] = true;
					}
				}
			}
		}
		
		currentDepth++;
	}
	
	// 确定下一步方向
	int direction = 2; // 默认向左
	
	if (foundPath) {
		// 回溯找到第一步
		int nextX = playerX;
		int nextY = playerY;
		int firstStepX = -1;
		int firstStepY = -1;
		
		// 回溯路径找到第一步
		while (true) {
			int parentX = nodeInfo[nextY][nextX].parentX;
			int parentY = nodeInfo[nextY][nextX].parentY;
			
			if (parentX == -1 || parentY == -1) {
				break; // 到达起点
			}
			
			if (parentX == ghostX && parentY == ghostY) {
				// 找到了第一步
				firstStepX = nextX;
				firstStepY = nextY;
				break;
			}
			
			nextX = parentX;
			nextY = parentY;
		}
		
		if (firstStepX != -1 && firstStepY != -1) {
			// 设置跟踪点
			*track_x = firstStepX;
			*track_y = firstStepY;
			
			// 确定方向
			if (ghostX < firstStepX) direction = 0;      // 右
			else if (ghostX > firstStepX) direction = 2; // 左
			else if (ghostY > firstStepY) direction = 1; // 上
			else if (ghostY < firstStepY) direction = 3; // 下
		} else {
			// 如果无法确定第一步，使用简单的方向判断
			if (ghostX < playerX) direction = 0;      // 右
			else if (ghostX > playerX) direction = 2; // 左
			else if (ghostY > playerY) direction = 1; // 上
			else if (ghostY < playerY) direction = 3; // 下
			
			// 设置跟踪点为幽灵当前位置
			*track_x = ghostX;
			*track_y = ghostY;
		}
	} else {
		// 如果没找到路径，尝试使用更智能的方向判断
		// 检查四个方向，选择不是墙且离玩家最近的方向
		int bestDir = -1;
		int minDist = INT_MAX;
		const int dx[4] = { 1, -1, 0, 0 };
		const int dy[4] = { 0, 0, -1, 1 };
		
		for (int i = 0; i < 4; i++) {
			int newX = ghostX + dx[i];
			int newY = ghostY + dy[i];
			
			// 检查边界和墙
			if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE || run_grid[newY][newX] == WALL) {
				continue;
			}
			
			// 计算到玩家的曼哈顿距离
			int dist = abs(playerX - newX) + abs(playerY - newY);
			if (dist < minDist) {
				minDist = dist;
				bestDir = i;
				*track_x = newX;
				*track_y = newY;
			}
		}
		
		// 如果找到了有效方向，使用它
		if (bestDir != -1) {
			direction = bestDir;
		} else {
			// 如果所有方向都是墙，使用简单的方向判断
			if (ghostX < playerX) direction = 0;      // 右
			else if (ghostX > playerX) direction = 2; // 左
			else if (ghostY > playerY) direction = 1; // 上
			else if (ghostY < playerY) direction = 3; // 下
			
			// 设置跟踪点为幽灵当前位置
			*track_x = ghostX;
			*track_y = ghostY;
		}
	}
	
	return direction;
}

void GamePacman::initGrid()
{
	int map[GRID_SIZE][GRID_SIZE] = { {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, WALL, FOOD, WALL, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, WALL, FOOD, WALL, FOOD, FOOD, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, WALL},
									 {WALL, WALL, FOOD, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, FOOD, WALL, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
									 {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
									 {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL} };
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
	player.y = 17;
	player.old_x = 6;
	player.old_y = 17;
	player.direction = Direction::LEFT;
	player.speed = 1;
	ghost[0].x = 12;
	ghost[0].y = 17;
	ghost[0].old_x = 12;
	ghost[0].old_y = 17;
	ghost[0].direction = Direction::RIGHT;//���½�
	ghost[0].speed = 1;
	ghost[0].live = 1;
	ghost[1].x = 2;
	ghost[1].y = 5;
	ghost[1].old_x = 2;
	ghost[1].old_y = 5;
	ghost[1].direction = Direction::LEFT;//���Ͻ�
	ghost[1].speed = 1;
	ghost[1].live = 1;
	ghost[2].x = 16;
	ghost[2].y = 5;
	ghost[2].old_x = 16;
	ghost[2].old_y = 5;
	ghost[2].direction = Direction::RIGHT;//���Ͻ�
	ghost[2].speed = 1;
	ghost[2].form = 0;
	ghost[2].live = 1;
	initimg = &player_img[1];
	canChangeDirection = false; // 初始化时允许改变方向
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

	canChangeDirection = true;
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
		if(player.x+1<=18)	
		{
			if (run_grid[player.y][player.x + 1] != WALL)
				player.x += player.speed;
		}
		else
		{
			player.x = 0;
		}
		break;
	case Direction::UP:
		if (run_grid[player.y - 1][player.x] != WALL)
			player.y -= player.speed;
		break;
	case Direction::LEFT:
		if (player.x-1>=0)
		{
			if (run_grid[player.y][player.x - 1] != WALL)
				player.x -= player.speed;
		}
		else
		{
			player.x = 18;
		}
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

	// 始终计算寻路方向，但根据moveCounter控制移动速度
	// 计算所有幽灵的寻路方向
	int dir1 = ghostDirection(ghost[0].x, ghost[0].y, player.x, player.y, &track_x, &track_y);
	int dir2 = ghostDirection(ghost[1].x, ghost[1].y, player.old_x, player.old_y, &track_x, &track_y);
	int dir3 = ghostDirection(ghost[2].x, ghost[2].y, 2*player.x-player.old_x, 2 * player.y - player.old_y, &track_x, &track_y);

	// 根据moveCounter控制移动速度
	if (moveCounter == 0)
	{
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

	// 保留moveCounter用于控制幽灵移动速度
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
			initimg = &player_img[1];
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
	display(getGrid(), 19);

	while (!gameOver)
	{
		if (_kbhit())
		{
			char input = _getch();
			if (input == 'q')
				break;
			update(input);
			display(getGrid(), 19);
		}

		else
		{
			update(' ');
			display(getGrid(), 19);
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
	loadimage(&Food, _T("./PictureResource/GamePacman/food.png"), 19, 19, true);
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
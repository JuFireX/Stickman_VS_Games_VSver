#include <windows.h>
#include <iostream>
#include "level_Pacman.h"

GamePacman::GamePacman() : rng(time(nullptr)) {}

int GamePacman::ghost1(int g_map_x, int g_map_y, int p_map_x, int p_map_y, int* g1_track_x, int* g1_track_y)
{
    int map1[20][20] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
    int trace[400][3];
    int k = 0, l = 0, derection = 2;
    trace[k][0] = g_map_x;
    trace[k][1] = g_map_y;
    trace[k][2] = 0;
    int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
    int pc = 0, pre = -1;
    map1[g_map_y][g_map_x] = 2;
    while (trace[k][0] != p_map_x || trace[k][1] != p_map_y)
    {
        if (pc == 0)
            pre++;
        if (map1[trace[pre][1] + dy[pc]][trace[pre][0] + dx[pc]] == 1)
        {
            k++;
            trace[k][0] = trace[pre][0] + dx[pc];
            trace[k][1] = trace[pre][1] + dy[pc];
            trace[k][2] = pre;
            map1[trace[pre][1] + dy[pc]][trace[pre][0] + dx[pc]] = 2;
        }
        pc = (pc + 1) % 4;
    }
    *g1_track_x = trace[pre][0];
    *g1_track_y = trace[pre][1];
    while (trace[k][2] != 0)
    {
        k = trace[k][2];
    }
    if ((g_map_x) < trace[k][0])
        derection = 0;
    if ((g_map_x) > trace[k][0])
        derection = 2;
    if ((g_map_y) > trace[k][1])
        derection = 1;
    if ((g_map_y) < trace[k][1])
        derection = 3;
    return derection;
}

void GamePacman::initGrid()
{
    // 鍦板浘
    int map[GRID_SIZE][GRID_SIZE] = {
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
        {WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL},
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
        }
    }
}

void GamePacman::initMovers()
{
    player.x = 1;
    player.y = 18;
    player.old_x = 1;
    player.old_y = 18;
    player.direction = Direction::RIGHT;
    player.speed = 1;
    ghost[0].x = 18;
    ghost[0].y = 1;
    ghost[0].old_x = 18;
    ghost[0].old_y = 1;
    ghost[0].direction = Direction::LEFT;
    ghost[0].speed = 1;
    ghost[0].live = 1;
    ghost[1].x = 18;
    ghost[1].y = 16;
    ghost[1].old_x = 18;
    ghost[1].old_y = 16;
    ghost[1].direction = Direction::LEFT;
    ghost[1].speed = 1;
    ghost[1].live = 1;
    ghost[2].x = 1;
    ghost[2].y = 1;
    ghost[2].old_x = 1;
    ghost[2].old_y = 1;
    ghost[2].direction = Direction::RIGHT;
    ghost[2].speed = 1;
    ghost[2].form = 0;
    ghost[2].live = 1;
}
void GamePacman::initGame()
{
    phase = 1;
    score = 0;
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
    // 娓呴櫎涔嬪墠鐨勭帺瀹跺拰楝奸瓊浣嶇疆
    run_grid[player.old_y][player.old_x] = EMPTY;
    run_grid[ghost[0].old_y][ghost[0].old_x] = EMPTY;
    run_grid[ghost[1].old_y][ghost[1].old_x] = EMPTY;
    run_grid[ghost[2].old_y][ghost[2].old_x] = EMPTY;

    // 鏇存柊鏂扮殑浣嶇疆
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
    case 'r': // 閲嶇疆鍏冲崱
        initGame();
        return true;
    case ' ':
        break;
    default:
        return false;
    }
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
    // 保存幽灵的旧位置
    ghost[0].old_x = ghost[0].x;
    ghost[0].old_y = ghost[0].y;
    ghost[1].old_x = ghost[1].x;
    ghost[1].old_y = ghost[1].y;
    ghost[2].old_x = ghost[2].x;
    ghost[2].old_y = ghost[2].y;

    // 使用ghost1函数控制幽灵移动
    int track_x, track_y;
    int dir = ghost1(ghost[0].x, ghost[0].y, player.x, player.y, &track_x, &track_y);

    // 根据返回的方向移动幽灵
    switch (dir)
    {
    case 0: // 右
        if (run_grid[ghost[0].y][ghost[0].x + 1] != WALL)
            ghost[0].x += ghost[0].speed;
        break;
    case 1: // 上
        if (run_grid[ghost[0].y - 1][ghost[0].x] != WALL)
            ghost[0].y -= ghost[0].speed;
        break;
    case 2: // 左
        if (run_grid[ghost[0].y][ghost[0].x - 1] != WALL)
            ghost[0].x -= ghost[0].speed;
        break;
    case 3: // 下
        if (run_grid[ghost[0].y + 1][ghost[0].x] != WALL)
            ghost[0].y += ghost[0].speed;
        break;
    }

    // 简单的随机移动逻辑用于其他幽灵
    for (int i = 1; i < 3; i++) {
        int random_dir = rng() % 4;
        switch (random_dir) {
        case 0: // 右
            if (run_grid[ghost[i].y][ghost[i].x + 1] != WALL)
                ghost[i].x += ghost[i].speed;
            break;
        case 1: // 上
            if (run_grid[ghost[i].y - 1][ghost[i].x] != WALL)
                ghost[i].y -= ghost[i].speed;
            break;
        case 2: // 左
            if (run_grid[ghost[i].y][ghost[i].x - 1] != WALL)
                ghost[i].x -= ghost[i].speed;
            break;
        case 3: // 下
            if (run_grid[ghost[i].y + 1][ghost[i].x] != WALL)
                ghost[i].y += ghost[i].speed;
            break;
        }
    }
}

void GamePacman::update(char key)
{
    if (processInput(key))
        movePlayer();

    // 移动幽灵
    moveGhosts();

    // 更新grid数组，确保幽灵显示
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

    // 检查玩家是否与幽灵碰撞
    for (int i = 0; i < 3; i++) {
        if (player.x == ghost[i].x && player.y == ghost[i].y) {
            // 玩家与幽灵碰撞，游戏结束
            phase = 0;
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
//已修改
int GamePacman::judgeScore()
{
    // 检查是否达到目标分数，并更新游戏阶段
    if (score >= target)
        phase = 2;
    return score;
}

int GamePacman::getScore() const
{
    return score;
}

GameState GamePacman::state() const
{
    // return phase==0 ? GameState::GameOver : GameState::Running;
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
                cout << "# "; // 墙壁
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
                cout << "  "; // 空白区域
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
    while (phase == 1)
    {
        if (_kbhit())
        {
            char input = _getch();
            if (input == 'q')
                break;
            update(input);

            display(getGrid(), 20);
            cout << "score:" << getScore() << "  " << "target:" << target << "  " << "phase:" << phase;
        }
        // 鑷�鏇存�?
        else
        {
            update(' ');
            display(getGrid(), 20);
            cout << "score:" << getScore() << "  " << "target:" << target << "  " << "phase:" << phase;
        }
        Sleep(1000 / 6);
    }
    while (phase == 0)
    {
        cout << "lose";
        Sleep(1000);
    }

    while (phase == 2)
    {
        cout << "win";
        Sleep(1000);
    }

}
//����Ϊ��Ⱦ����
void GamePacman::load()  
{  
   // �޸�����ȷ��·���Ͳ�����ȷ  
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

vector<vector<position>> GamePacman::getMap() const // �ػ��ͼ
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
                GameMap[2+i][8+j].val = state[i][j];
            }
        }
    }
    return GameMap;
}
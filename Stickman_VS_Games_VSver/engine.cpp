// engine.cpp
#include <memory>
#include <vector>
#include <iostream>
#include "engine.h"
#include "level_2048.h"
#include <cstring>
#include <string>
#include <graphics.h>
// ...

using namespace std;

Game2048* game = new Game2048();

Engine::Engine() {}

void Engine::init()
{
    bool fuck = true;
    initgraph(wide, high);//创建画布
    setbkcolor(WHITE);// 设置背景色为白色
    cleardevice();
    load();
}

void Engine::draw()
{
    //减少运行资源
    
    //绘制地图
    for (int i = 0; i < 24; i++)
    {
        for (position u : GameMap[i])
        {
            putimage(u.x, u.y, &game->MapImg[u.val]);
        }
    }

    FlushBatchDraw();

   
}

void Engine::load()//n为素材数量
{
    game->load();
}

void Engine::drawGameMap()
{
    sizeY = high / 24;
    sizeX = wide / 36;
    for (int i = 0; i < 24; i++) {
        vector<position> row;
        for (int j = 0; j < 36; j++) {
            row.push_back({ -1, j * sizeX, i * sizeY });
        }
        GameMap.push_back(row);
    }
    
    //图像位置代码
    vector<vector<int>>state = game->getGrid();
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
}






void Engine::display(const vector<vector<int>> &grid, int size)
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

void Engine::run()
{
    

    game->initGame();
    display(game->getGrid(), 4);
    BeginBatchDraw();
    while (true)
    {
        DWORD start_time = GetTickCount();
        drawGameMap();
        cleardevice();
        draw();
		while (peekmessage(&msg))//用于画布显示
		{
            if (msg.message == WM_KEYDOWN)
            {
                if (msg.vkcode == VK_ESCAPE)
                {
                    running = false;
                    break;
                }
                else if (msg.vkcode == VK_UP||msg.vkcode== 'W')
                {
                    game->update('w');
                    display(game->getGrid(), 4);
                    
                }
                else if (msg.vkcode == VK_DOWN||msg.vkcode=='S')
                {
                    game->update('s');
                    display(game->getGrid(), 4);
				
                }
                else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
                {
                    game->update('a');
                    display(game->getGrid(), 4);
                    
                }
                else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
                {
                    game->update('d');
                    display(game->getGrid(), 4);
                  
                }
            }
		}


        /*char input = _getch();//用于命令行显示
        if (input == 'q')
            break;
        game->update(input);
        display(game->getGrid(), 4);*/


        //减少游戏运行资源
        DWORD end_time = GetTickCount();
        DWORD dalta_time = start_time - end_time;
        if (dalta_time <= 1000 / 60)
        {
            Sleep(dalta_time);
        }
    }

    EndBatchDraw();
}

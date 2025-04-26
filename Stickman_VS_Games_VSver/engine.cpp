// engine.cpp
#include <memory>
#include <vector>
#include <iostream>
#include "engine.h"
//#include "level_2048.h"
#include <cstring>
#include <string>
#include <graphics.h>
#include "level_Snake.h"
// ...

using namespace std;

//Game2048* game = new Game2048();
GameSnake* game = new GameSnake();

Engine::Engine() {}

void Engine::init()
{
    bool fuck = true;
    initgraph(wide, high);//��������
    setbkcolor(WHITE);// ���ñ���ɫΪ��ɫ
    cleardevice();
    load();
}

void Engine::draw()
{
    //����������Դ
    //���Ƶ�ͼ
    for (int i = 0; i < game->GameHigh; i++)
    {
        for (position u : GameMap[i])
        {
            putimage(u.x, u.y, &game->MapImg[u.val]);
        }
    }
    FlushBatchDraw();
}

void Engine::load()//nΪ�ز�����
{
    game->load();
}
void Engine::drawGameMap()
{
   GameMap = game->getMap();
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
    display(game->getGrid(),game->GridSize);
    BeginBatchDraw();
    while (true)
    {
        DWORD start_time = GetTickCount();
        game->update(' ');
        drawGameMap();
        cleardevice();
        draw();

		bool moveright = false;
		bool moveleft = false;
		bool moveup = false;
		bool movedown = false;
		while (peekmessage(&msg))//���ڻ�����ʾ
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
                    moveup = true;
                }
                else if (msg.vkcode == VK_DOWN||msg.vkcode=='S')
                {
					movedown = true;
				
                }
                else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
                {
					moveleft = true;
                }
                else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
                {
					moveright = true;
                }
            }
		}

		if (moveup)
		{
			game->update('w');
		}
		else if (movedown)
		{
			game->update('s');
		}
		else if (moveleft)
		{
			game->update('a');
		}
		else if (moveright)
		{
			game->update('d');
		}
        /*char input = _getch();//������������ʾ
        if (input == 'q')
            break;
        game->update(input);
        display(game->getGrid(), 4);*/
        //������Ϸ������Դ
        DWORD end_time = GetTickCount();
        DWORD dalta_time = start_time - end_time;
        if (dalta_time <= 1000 / 120)
        {
            Sleep(dalta_time);
        }
    }

    EndBatchDraw();
}

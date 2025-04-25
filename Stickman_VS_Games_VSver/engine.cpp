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

Engine::Engine() {}

void Engine::init()
{
    bool fuck = true;
    initgraph(wide, high);//��������
    setbkcolor(WHITE);// ���ñ���ɫΪ��ɫ
    cleardevice();
    load(0);
}

void Engine::draw()
{
    //����������Դ
    
    //���Ƶ�ͼ
    for (int i = 0; i < MapSizeY; i++)
    {
        for (position u : GameMap[i])
        {
            putimage(u.x, u.y, &MapImg[u.val]);
        }
    }

    FlushBatchDraw();

   
}

void Engine::load(int n)//nΪ�ز�����
{
    for (int i = 0; i < n; i++)
    {
        wstring path = L"..//PictureResource//" + to_wstring(i) + L".png";
        loadimage(&MapImg[i], path.c_str());
    }
}

void Engine::drawGameMap()
{
    sizeY = high / 24;
    sizeX = wide / 36;
    for (int i = 0; i < 24; i++) {
        vector<position> row;
        for (int j = 0; j < 36; j++) {
            row.push_back({ 0, j * sizeX, i * sizeY });
        }
        GameMap.push_back(row);
    }
    //ͼ��λ�ô���
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
    Game2048 *game = new Game2048();

    game->initGame();
    display(game->getGrid(), 4);
    BeginBatchDraw();
    while (true)
    {
        DWORD start_time = GetTickCount();
        drawGameMap();
        cleardevice();
        draw();
		while (peekmessage(&msg, EM_MOUSE | EM_KEY | EM_CHAR, true))//���ڻ�����ʾ
		{
			if (msg.message == EM_KEY)
			{
				if (msg.vkcode == VK_ESCAPE)
				{
					running = false;
					break;
				}
			}
			else if (msg.message == EM_CHAR)
			{
				char input = msg.ch;
				game->update(input);
				display(game->getGrid(), 4);
			}
		}


        char input = _getch();//������������ʾ
        if (input == 'q')
            break;
        game->update(input);
        display(game->getGrid(), 4);


        //������Ϸ������Դ
        DWORD end_time = GetTickCount();
        DWORD dalta_time = start_time - end_time;
        if (dalta_time <= 1000 / 60)
        {
            Sleep(dalta_time);
        }
    }
    EndBatchDraw();
}

// engine.cpp
//WARNING:˽�˴�������

#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <graphics.h>
#include "level_2048.h"
#include "level_Snake.h"
#include "engine.h"

// ...

using namespace std;

//Game2048* game = new Game2048();
GameSnake *game = new GameSnake();

Engine::Engine() {}

void Engine::init()
{
    bool fuck = true;
    initgraph(width, height); // ��������
    setbkcolor(WHITE);        // ���ñ���ɫΪ��ɫ
    cleardevice();
    load();
}

void Engine::draw()
{
    // ����������Դ
    // ���Ƶ�ͼ
    for (int i = 0; i < game->GameHigh; i++)
    {
        for (position u : GameMap[i])
        {
            putimage(u.x, u.y, &game->MapImg[u.val]);
        }
    }
    FlushBatchDraw();
}

void Engine::load() // nΪ�ز�����
{
    game->load();
}
void Engine::drawGameMap()
{
    GameMap = game->getMap();
}

void Engine::MessageHandle()
{
    bool moveRight = false;
    bool moveLeft = false;
    bool moveUp = false;
    bool moveDown = false;


    while (peekmessage(&msg)) // ���ڻ�����ʾ
    {
        if (msg.message == WM_KEYDOWN)
        {
            if (msg.vkcode == VK_ESCAPE)
            {
                running = false;
                break;
            }
            else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
            {
                moveUp = true;
            }
            else if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
            {
                moveDown = true;
            }
            else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
            {
                moveLeft = true;
            }
            else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
            {
                moveRight = true;
            }
        }
    }


    if (moveUp)
    {
        game->update('w');
    }
    else if (moveDown)
    {
        game->update('s');
    }
    else if (moveLeft)
    {
        game->update('a');
    }
    else if (moveRight)
    {
        game->update('d');
    }
    else
    {
        game->update(' ');
    }

}

void Engine::run()
{
    game->initGame();
    BeginBatchDraw();
    while (true)
    {
        DWORD start_time = GetTickCount();
        
        drawGameMap();
        cleardevice();
        draw();

		MessageHandle();
        /*char input = _getch();//������������ʾ
        if (input == 'q')
            break;
        game->update(input);
        display(game->getGrid(), 4);*/

        // ��Ϸˢ��
        DWORD end_time = GetTickCount();
        DWORD delta_time = start_time - end_time;
        
        if (delta_time <= 1000 / game->GameFrame)
        {
            Sleep(delta_time);
         }
    }

    EndBatchDraw();
}

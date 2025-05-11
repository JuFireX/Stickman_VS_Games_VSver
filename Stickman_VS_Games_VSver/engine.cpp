// engine.cpp

#include <memory>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <graphics.h>
#include "level_2048.h"
#include "level_Snake.h"
#include "level_Sokoban.h"
#include "engine.h"
#include <windows.h>
#include <wingdi.h>

// ...
using namespace std;
Engine::Engine() {}

/*Game2048* game = new Game2048();

void Engine::render()
{
    GameMap = game->getMap();
    for (int i = 0; i < game->GameHigh; i++)
    {
        for (position u : GameMap[i])
        {
            putimage(u.x, u.y, &game->MapImg[u.val]);
        }
    }
    FlushBatchDraw();
}

void Engine::MessageHandle()
{
	bool moveRight = false;
	bool moveLeft = false;
	bool moveUp = false;
	bool moveDown = false;

    while (peekmessage(&msg))
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

void Engine::init()
{
    bool fuck = true;
    initgraph(width, height); // ��������
    setbkcolor(WHITE);        // ���ñ���ɫΪ��ɫ
    cleardevice();
    game->load();
}

void Engine::run()
{
    
    game->initGame();
    BeginBatchDraw();
    while (!game->gameOver)
    {
        
        cleardevice();
        render();

		MessageHandle();

        Sleep(1000/6);

    }
    EndBatchDraw();
}


void Engine::close()
{
	closegraph();
	delete game;
}*/
#pragma comment(lib, "MSIMG32.LIB")
inline void Engine::putimage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();

    // 定义 BLENDFUNCTION 结构
    BLENDFUNCTION blendFunction;
    blendFunction.BlendOp = AC_SRC_OVER;  // 指定源图像覆盖目标图像
    blendFunction.BlendFlags = 0;         // 必须为 0
    blendFunction.SourceConstantAlpha = 255; // 全不透明 (0-255)
    blendFunction.AlphaFormat = AC_SRC_ALPHA; // 使用源图像的 alpha 通道

    // 调用 AlphaBlend 函数
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, blendFunction);
}
void Engine::runGame2048()
{

    bool fuck = true;

    Game2048* game = new Game2048();

    initgraph(width, height); // ��������
    setbkcolor(WHITE);        // ���ñ���ɫΪ��ɫ
    cleardevice();
    game->load();

    game->initGame();
    BeginBatchDraw();
    while (!game->gameOver)
    {

        cleardevice();

        GameMap = game->getMap();
        for (int i = 0; i < game->GameHigh; i++)
        {
            for (position u : GameMap[i])
            {
                putimage(u.x, u.y, &game->MapImg[u.val]);
            }
        }
        FlushBatchDraw();

        bool moveRight = false;
        bool moveLeft = false;
        bool moveUp = false;
        bool moveDown = false;


        while (peekmessage(&msg))
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

        Sleep(1000 / game->GameFrame);

    }
    EndBatchDraw();
    closegraph();
    delete game;
}

void Engine::runGameSnake()
{
    bool fuck = true;

    GameSnake* game = new GameSnake();

    initgraph(width, height); // ��������
    setbkcolor(WHITE);        // ���ñ���ɫΪ��ɫ
    cleardevice();
    game->load();

    game->initGame();
    BeginBatchDraw();
    while (!game->gameOver)
    {
        bool moveRight = false;
        bool moveLeft = false;
        bool moveUp = false;
        bool moveDown = false;


        while (peekmessage(&msg))
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
        if (moveDown)
        {
            game->update('s');
        }
        if (moveLeft)
        {
            game->update('a');
        }
        if (moveRight)
        {
            game->update('d');
        }
		if (!moveUp && !moveDown && !moveLeft && !moveRight)
        {
            game->update(' ');
        }
        cleardevice();

        GameMap = game->getMap();
        for (int i = 0; i < game->GameHigh; i++)
        {
            for (position u : GameMap[i])
            {
                putimage(u.x, u.y, &game->MapImg[u.val]);
            }
        }
        FlushBatchDraw();

        Sleep(1000 / game->GameFrame);

    }
    EndBatchDraw();
    closegraph();
    delete game;
}

void Engine::runGameSokoban()
{
    bool fuck = true;

    GameSokoban* game = new GameSokoban();

    initgraph(width, height); // ��������
    setbkcolor(WHITE);        // ���ñ���ɫΪ��ɫ
    cleardevice();
    game->load();

    game->initGame();
    BeginBatchDraw();
    while (!game->gameOver)
    {
        bool moveRight = false;
        bool moveLeft = false;
        bool moveUp = false;
        bool moveDown = false;


        while (peekmessage(&msg))
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
        if (moveDown)
        {
            game->update('s');
        }
        if (moveLeft)
        {
            game->update('a');
        }
        if (moveRight)
        {
            game->update('d');
        }
        if (!moveUp && !moveDown && !moveLeft && !moveRight)
        {
            game->update(' ');
        }
        cleardevice();

        GameMap = game->getMap();
        for (int i = 0; i < game->GameHigh; i++)
        {
            for (position u : GameMap[i])
            {
                putimage_alpha(u.x, u.y, &game->MapImg[u.val]);
            }
        }
        FlushBatchDraw();

        Sleep(1000 / game->GameFrame);

    }
    EndBatchDraw();
    closegraph();
    delete game;
}

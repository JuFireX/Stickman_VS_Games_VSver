// engine.cpp
#include "engine.h"
#include "level_2048.h"
#include "level_pacman.h"
#include "level_Snake.h"
#include "level_Sokoban.h"
#include "level_Tetris.h"
#include <cstring>
#include <graphics.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <wingdi.h>
#pragma comment(lib, "MSIMG32.LIB")

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
	initgraph(width, height); // ????????
	setbkcolor(WHITE);        // ????????????
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

inline void Engine::putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();

	// 定义 BLENDFUNCTION 结构
	BLENDFUNCTION blendFunction;
	blendFunction.BlendOp = AC_SRC_OVER;      // 指定源图像覆盖目标图像
	blendFunction.BlendFlags = 0;             // 必须为 0
	blendFunction.SourceConstantAlpha = 255;  // 全不透明 (0-255)
	blendFunction.AlphaFormat = AC_SRC_ALPHA; // 使用源图像的 alpha 通道

	// 调用 AlphaBlend 函数
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, blendFunction);
}

void Engine::runGame2048()
{

	bool fuck = true;

	Game2048* game = new Game2048();

	initgraph(width, height);
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// 切换到美式英文输入法
	HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
	setbkcolor(WHITE);   // 设置背景色
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
		bool if_quit = false;

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
				else if (msg.vkcode == VK_ESCAPE || msg.vkcode == 'Q')
				{
					if_quit = true;
					break;
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
		if (if_quit)
		{
			running = false;
			break;
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

	initgraph(width, height); // 初始化窗口
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// 切换到美式英文输入法
	HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	// setbkcolor(WHITE);        // 设置背景色
	cleardevice();
	game->load();

	game->initGame();
	BeginBatchDraw();
	while (!game->gameOver)
	{
		char inputKey = ' ';

		// 只保留最后一个方向键消息
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
					inputKey = 'w';
				}
				else if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					inputKey = 's';
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
				{
					inputKey = 'a';
				}
				else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
				{
					inputKey = 'd';
				}
			}
		}

		game->update(inputKey);
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

void Engine::runGameSokoban()
{
	bool fuck = true;

	GameSokoban* game = new GameSokoban();

	initgraph(width, height);
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// 切换到美式英文输入法
	HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
	// setbkcolor(WHITE);   // 设置背景色
	cleardevice();
	game->load();

	game->initGame();
	BeginBatchDraw();
	while (!game->gameOver)
	{
		char inputKey = ' ';

		// 只保留最后一个方向键消息
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE || msg.vkcode == 'Q')
				{
					game->gameOver = true;
					break;
				}
				else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
				{
					inputKey = 'w';
				}
				else if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					inputKey = 's';
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
				{
					inputKey = 'a';
				}
				else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
				{
					inputKey = 'd';
				}
				else if (msg.vkcode == 'R')
				{
					inputKey = 'r';
				}
			}
		}

		// 每帧只处理最后一个方向输入
		game->update(inputKey);
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

void Engine::runGameTetris()
{
	bool fuck = true;

	GameTetris* game = new GameTetris();

	initgraph(width, height);
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// 切换到美式英文输入法
	// 切换到美式英文输入法（"00000409"）
	HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);

	// setbkcolor(WHITE);        // 设置背景色
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();
	while (!game->gameOver)
	{

		char inputKey = ' ';

		// 只保留最后一个方向键消息
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE)
				{
					game->gameOver = true;
					break;
				}
				else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
				{
					inputKey = 'w';
				}
				else if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					inputKey = 's';
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
				{
					inputKey = 'a';
				}
				else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
				{
					inputKey = 'd';
				}
			}
		}

		// 每帧只处理最后一个方向输入
		game->update(inputKey);
		cleardevice();
		putimage_alpha(0, 0, &game->img_Tetris[6]);
		putimage_alpha(560, 160, &game->img_Tetris[3]);
		putimage_alpha(42, 42, &game->img_Tetris[4]);
		putimage_alpha(370, 60, &game->img_Tetris[5]);
		putimage_alpha(80, 200, &game->img_Tetris[8]);
		// 绘制游戏地图
		GameMap = game->getMap();
		for (int i = 0; i < game->GameHigh; i++)
		{
			for (position u : GameMap[i])
			{
				putimage_alpha(u.x, u.y, &game->MapImg[u.val]);
			}
		}
		putimage_alpha(0, 400, &game->img_Tetris[7]);
		FlushBatchDraw();

		Sleep(1000 / game->GameFrame);
	}

	EndBatchDraw();
	closegraph();
	delete game;
}

void Engine::runGamePacman()
{
	bool fuck = true;

	GamePacman* game = new GamePacman();

	initgraph(width, height);
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);
	// 切换到美式英文输入法
	HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);

	// setbkcolor(WHITE);        // 设置背景色
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();
	int cntframe = 0;
	int cnt_ad = 0;
	IMAGE* img = &game->player_img[0];
	while (!game->gameOver)
	{

		char inputKey = ' ';

		// 只保留最后一个方向键消息
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE || msg.vkcode == 'Q')
				{
					game->phase = 0;
					break;
				}
				else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
				{
					inputKey = 'w';
				}
				else if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					inputKey = 's';
				}
				else if (msg.vkcode == VK_LEFT || msg.vkcode == 'A')
				{
					inputKey = 'a';
				}
				else if (msg.vkcode == VK_RIGHT || msg.vkcode == 'D')
				{
					inputKey = 'd';
				}
				else if (msg.vkcode == 'R')
				{
					inputKey = 'r';
				}
			}
		}

		// 每帧只处理最后一个方向输入
		game->update(inputKey);

		cleardevice();
		GameMap = game->getMap();
		switch (inputKey)
		{
		case 'w':
			img = &game->player_img[2];
			break; // 上
		case 's':
			img = &game->player_img[3];
			break; // 下
		case 'a':
			img = &game->player_img[1];
			break; // 左
		case 'd':
			img = &game->player_img[0];
			break; // 右
		default:
			break;
		}

		for (int i = 0; i < game->GameHigh; i++)
		{
			for (position u : GameMap[i])
			{
				if (u.val == 2)
				{
					if (cntframe % 2 == 0)
						cnt_ad++;
					if (cnt_ad % 2 == 0)
					{
						putimage_alpha(u.x, u.y, &game->player_img[4]);
					}
					else
					{
						putimage_alpha(u.x, u.y, img);
					}
				}
				else
				{
					putimage_alpha(u.x, u.y, &game->MapImg[u.val]);
				}
			}
		}

		FlushBatchDraw();
		cntframe++;
		Sleep(1000 / game->GameFrame);
	}

	EndBatchDraw();
	closegraph();
	delete game;
}

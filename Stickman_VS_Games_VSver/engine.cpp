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

inline void Engine::putimage_alpha(int x, int y, IMAGE* img, int alpha)
{
	int w = img->getwidth();
	int h = img->getheight();

	// ���� BLENDFUNCTION �ṹ
	BLENDFUNCTION blendFunction;
	blendFunction.BlendOp = AC_SRC_OVER;      // ָ��Դͼ�񸲸�Ŀ��ͼ��
	blendFunction.BlendFlags = 0;             // ����Ϊ 0
	blendFunction.SourceConstantAlpha = alpha;// ȫ��͸�� (0-255)
	blendFunction.AlphaFormat = AC_SRC_ALPHA; // ʹ��Դͼ��� alpha ͨ��

	// ���� AlphaBlend ����
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, blendFunction);
}

void Engine::fadeout_clear_screen(int width, int height, int steps, int delay)
{
	IMAGE mask;
	loadimage(&mask, _T("./PictureResource/white.png"), width, height, true);
	int cnt = 0;
	for (int i = 1; i <= steps; ++i)
	{
		int alpha = i * 255 / steps;
		putimage_alpha(0, 0, &mask, alpha);
		FlushBatchDraw();
		Sleep(delay);
		cnt += alpha;
		if (cnt > 8000)
		{
			break;
		}
	}
	Sleep(2000);
}

void Engine::FadeInWHITE(int width, int height, int steps, int delay)
{
	// �Ƚ�ȡ��ǰ��Ļ����
	IMAGE screen;
	getimage(&screen, 0, 0, width, height);

	// ����һ�Ű�ɫ����
	IMAGE mask;
	loadimage(&mask, _T("./PictureResource/white.png"), width, height, true);

	for (int i = steps; i >= 0; --i)
	{
		// �Ȼ���Ϸ����
		putimage(0, 0, &screen);

		// ���Ӱ�ɫ���֣�alpha��255->0
		int alpha = i * 255 / steps;
		putimage_alpha(0, 0, &mask, alpha);

		FlushBatchDraw();
		Sleep(delay);
	}
}

void Engine::FadeInBLACK(int width, int height, int steps, int delay)
{
	// �Ƚ�ȡ��ǰ��Ļ����
	IMAGE screen;
	getimage(&screen, 0, 0, width, height);

	// ����һ�Ű�ɫ����
	IMAGE mask;
	loadimage(&mask, _T("./PictureResource/white.png"), width, height, true);

	for (int i = steps; i >= 0; --i)
	{
		// �Ȼ���Ϸ����
		putimage(0, 0, &screen);

		// ���Ӱ�ɫ���֣�alpha��255->0
		int alpha = i * 255 / steps;
		putimage_alpha(0, 0, &mask, alpha);

		FlushBatchDraw();
		Sleep(delay);
	}
}

void Engine::initGame()
{
	initgraph(width, height);
	HWND hwnd = GetHWnd();
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// �л�����ʽӢ�����뷨
	//HKL hkl = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
	//ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
}

void Engine::runGame2048()
{
	bool fuck = true;
	Game2048* game = new Game2048();

	setbkcolor(WHITE);   // ���ñ���ɫ
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();
	GameMap = game->getMap();
	for (int i = 0; i < game->GameHigh; i++)
	{
		for (position u : GameMap[i])
		{
			putimage(u.x, u.y, &game->MapImg[u.val]);
		}
	}
	FadeInWHITE(720, 480, 255, 10);
	FlushBatchDraw();
	while (!game->gameOver)
	{
		bool moveRight = false;
		bool moveLeft = false;
		bool moveUp = false;
		bool moveDown = false;
		bool if_quit = false;

		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE || msg.vkcode == 'Q')
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

	fadeout_clear_screen(width, height, 255, 10);
	EndBatchDraw();
	delete game;
}

void Engine::runGameSnake()
{
	bool fuck = true;
	GameSnake* game = new GameSnake();
	setbkcolor(BLACK);
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();

	GameMap = game->getMap();
	for (int i = 0; i < game->GameHigh; i++)
	{
		for (position u : GameMap[i])
		{
			putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
		}
	}
	FadeInWHITE(720, 480, 255, 10);
	FlushBatchDraw();

	while (!game->gameOver)
	{
		char inputKey = ' ';

		// ֻ�������һ���������Ϣ
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE || msg.vkcode == 'Q')
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
				putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
			}
		}
		FlushBatchDraw();
		Sleep(1000 / game->GameFrame);
	}

	fadeout_clear_screen(width, height, 255, 10);
	EndBatchDraw();
	//closegraph();
	setbkcolor(WHITE);
	cleardevice();
	delete game;
}

void Engine::runGameSokoban()
{
	bool fuck = true;
	GameSokoban* game = new GameSokoban();

	setbkcolor(BLACK);
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();

	GameMap = game->getMap();
	for (int i = 0; i < game->GameHigh; i++)
	{
		for (position u : GameMap[i])
		{
			putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
		}
	}
	FadeInWHITE(720, 480, 255, 10);
	FlushBatchDraw();

	while (!game->gameOver)
	{
		char inputKey = ' ';

		// ֻ�������һ���������Ϣ
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

		// ÿֻ֡�������һ����������
		game->update(inputKey);
		cleardevice();

		GameMap = game->getMap();
		for (int i = 0; i < game->GameHigh; i++)
		{
			for (position u : GameMap[i])
			{
				putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
			}
		}
		FlushBatchDraw();
		Sleep(1000 / game->GameFrame);
	}

	fadeout_clear_screen(width, height, 255, 10);
	EndBatchDraw();
	//closegraph();
	setbkcolor(WHITE);
	cleardevice();
	delete game;
}

void Engine::runGameTetris()
{
	bool fuck = true;
	GameTetris* game = new GameTetris();

	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();
	putimage_alpha(0, 0, &game->img_Tetris[6], 255);
	putimage_alpha(560, 160, &game->img_Tetris[3], 255);
	putimage_alpha(42, 42, &game->img_Tetris[4], 255);
	putimage_alpha(370, 60, &game->img_Tetris[5], 255);
	putimage_alpha(80, 200, &game->img_Tetris[8], 255);
	// ������Ϸ��ͼ
	GameMap = game->getMap();
	for (int i = 0; i < game->GameHigh; i++)
	{
		for (position u : GameMap[i])
		{
			if(u.val!=2)
				putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
		}
	}
	putimage_alpha(0, 400, &game->img_Tetris[7], 255);
	FadeInWHITE(720, 480, 255, 10);
	FlushBatchDraw();
	while (!game->gameOver)
	{

		char inputKey = ' ';

		// ֻ�������һ���������Ϣ
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
			}
		}

		// ÿֻ֡�������һ����������
		game->update(inputKey);
		cleardevice();

		putimage_alpha(0, 0, &game->img_Tetris[6], 255);
		putimage_alpha(560, 160, &game->img_Tetris[3], 255);
		putimage_alpha(42, 42, &game->img_Tetris[4], 255);
		putimage_alpha(370, 60, &game->img_Tetris[5], 255);
		putimage_alpha(80, 200, &game->img_Tetris[8], 255);

		// ������Ϸ��ͼ
		GameMap = game->getMap();
		for (int i = 0; i < game->GameHigh; i++)
		{
			for (position u : GameMap[i])
			{
				putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
			}
		}
		putimage_alpha(0, 400, &game->img_Tetris[7], 255);
		FlushBatchDraw();
		Sleep(1000 / game->GameFrame);
	}

	fadeout_clear_screen(width, height, 255, 10);
	EndBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	//closegraph();
	delete game;
}

void Engine::runGamePacman()
{
	bool fuck = true;
	GamePacman* game = new GamePacman();

	setbkcolor(BLACK);        // ���ñ���ɫ
	cleardevice();
	game->load();
	game->initGame();
	BeginBatchDraw();

	int cntframe = 0;
	int cnt_ad = 0;
	IMAGE* img = &game->player_img[0];
	game->update(' ');
	GameMap = game->getMap();
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
					putimage_alpha(u.x, u.y, &game->player_img[4], 255);
				}
				else
				{
					putimage_alpha(u.x, u.y, img, 255);
				}
			}
			else
			{
				putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
			}
		}
	}

	FadeInWHITE(720, 480, 255, 10);
	FlushBatchDraw();
	while (!game->gameOver)
	{
		char inputKey = ' ';

		// ֻ�������һ���������Ϣ
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

		// ÿֻ֡�������һ����������
		game->update(inputKey);

		cleardevice();
		GameMap = game->getMap();
		if(game->canChangeDirection)
			switch (inputKey)
			{
			case 'w':
				img = &game->player_img[2];
				break; // ��
			case 's':
				img = &game->player_img[3];
				break; // ��
			case 'a':
				img = &game->player_img[1];
				break; // ��
			case 'd':
				img = &game->player_img[0];
				break; // ��
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
						putimage_alpha(u.x, u.y, &game->player_img[4], 255);
					}
					else
					{
						putimage_alpha(u.x, u.y, img, 255);
					}
				}
				else
				{
					putimage_alpha(u.x, u.y, &game->MapImg[u.val], 255);
				}
			}
		}
		FlushBatchDraw();
		cntframe++;
		Sleep(1000 / game->GameFrame);
	}

	fadeout_clear_screen(width, height, 255, 10);
	EndBatchDraw();
	delete game;
}

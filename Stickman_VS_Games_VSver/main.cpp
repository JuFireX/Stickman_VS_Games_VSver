#include "engine.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

static const int BASIC_X = 10, BASIC_Y = 370, BASIC_H = 20;
static int x = BASIC_X, y = BASIC_Y;

// ת��GBK����Ϊ���ַ���
static wstring gbk_to_wstring(const string& str)
{
	int len = MultiByteToWideChar(936, 0, str.c_str(), -1, NULL, 0); // 936=GBK
	wstring wstr(len, L'\0');
	MultiByteToWideChar(936, 0, str.c_str(), -1, &wstr[0], len);
	// ȥ��ĩβ��\0
	if (!wstr.empty() && wstr.back() == L'\0')
		wstr.pop_back();
	return wstr;
}

// �����������
static void clearRect(COLORREF color)
{
	setfillcolor(color);
	solidrectangle(720, BASIC_Y, 0, 480);
	y = BASIC_Y;
}

// ���� cls
static void clean()
{
	cleardevice();
	y = BASIC_Y;
}

// �ȴ��û����� pause
static void pause(int timeout)
{
	flushmessage(-1);
	if (timeout == -1)
	{
		if (y >= 460)
		{
			y = BASIC_Y;
			cleardevice();
		}
		outtextxy(10, y, _T(">>>"));
		y += BASIC_H;

		FlushBatchDraw();
		ExMessage getmessage(BYTE filter = EX_KEY);
		getmessage();
	}
	else
	{
		Sleep(timeout * 1000); // ��������޷������ȴ�,��Ҫ�޸��߼�
	}
}

// ģ����ʽ���
static void streamOutput(const string text, int speed, int timeout, int color = WHITE)
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWeight = FW_BOLD;
	f.lfOutPrecision = OUT_TT_PRECIS;
	wcscpy_s(f.lfFaceName, _T("Arial"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	settextcolor(color);

	// ת��
	wstring wtext = gbk_to_wstring(text);
	wstring out;
	flushmessage();

	if (y >= 460)
	{
		clearRect(BLACK);
	}
	for (wchar_t wc : wtext)
	{
		out += wc;
		outtextxy(x, y, out.c_str());
		flushmessage();
		Sleep(speed);
	}

	y += BASIC_H;
	pause(timeout);
}

// �������
static void directOutput(const string text, int timeout, int color = WHITE)
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWeight = FW_BOLD;
	f.lfOutPrecision = OUT_TT_PRECIS;
	wcscpy_s(f.lfFaceName, _T("Arial"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	settextcolor(color);

	// ת��
	wstring wtext = gbk_to_wstring(text);
	flushmessage();

	if (y >= 460)
	{
		clearRect(BLACK);
	}

	outtextxy(x, y, wtext.c_str());
	FlushBatchDraw();

	y += BASIC_H;
	pause(timeout);
}


// ���ѡ��
int choiceOutput(const string& output, const vector<string>& choices, int basec = WHITE, int selectc = RED)
{
	int select = 0;
	int n = (int)choices.size();
	int base_x = 480, base_y = BASIC_Y - 10 - (n + 1) * BASIC_H, line_h = BASIC_H;
	streamOutput(output, 10, 1, basec);

	while (true)
	{
		for (int i = 1; i <= n; ++i)
		{
			wstring wstr = gbk_to_wstring(to_string(i) + " -> " + choices[i - 1]);
			int y_chioce = base_y + i * line_h;
			if (i == select + 1)
			{
				settextcolor(selectc);
				outtextxy(base_x, y_chioce, wstr.c_str());
			}
			else
			{
				settextcolor(basec);
				outtextxy(base_x, y_chioce, wstr.c_str());
			}
		}
		FlushBatchDraw();

		ExMessage msg;
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					select = ((select + 1) % n);
					continue;
				}
				else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
				{
					select = ((select + n - 1) % n);
					continue;
				}
				else if (msg.vkcode == VK_RETURN || msg.vkcode == 'F')
				{
					return select + 1;
				}
				else if ((msg.vkcode - '0') >= 1 && (msg.vkcode - '0') <= n)
				{
					select = (msg.vkcode - '0');
					return select;
				}
				else
				{
					continue;
				}
			}
		}
		Sleep(10);
	}
}

// ���ͼƬ
static void putImg(int x, int y, int width, int height, string path, int timeout)
{
	IMAGE temp;
	Engine* engine1 = new Engine();
	std::wstring wpath = std::wstring(path.begin(), path.end());
	loadimage(&temp, wpath.c_str(), width, height);
	engine1->putimage_alpha(x, y, &temp, 255);
	FlushBatchDraw();
	pause(timeout);
	delete engine1;
}

// ��ʼ��
void initGameCli(int count)
{
	FreeConsole();
	if (count == 1)
		directOutput("�����ʵ�һ��Ŀ��� :P", 1);
	else if (count == 2)
		directOutput("Ŷ��? hello, again? ", 1);
	else if (count == 5)
		directOutput("��? ���ڸ���?? ", 1);
	else
		directOutput("������~~", 1);
}

// ������
int main()
{
	int count = 1;
	int temp = 0;
BEGINING:
	Engine* engine = new Engine();
	vector<string> choices;
	int choice = 0;
	engine->initGame();
	setbkcolor(BLACK);
	// ���±�Ļ
	initGameCli(count++);
	clean();
	putImg(0, 0, 720, 360, "./PictureResource/CG/1.png", 0);
	streamOutput("��������, �������ĵ���2048...", 50, 1);
	directOutput("(������2048ΪĿ������ж�)", -1);

	// ����
	streamOutput("WASD�ƶ�, Q��������.", 10, 2);
	setbkcolor(WHITE);
	engine->runGame2048();
	engine->FadeOut(720, 480, "./PictureResource/black.png", 10, 1);
	setbkcolor(BLACK);
	clean();

	// ��һ�ر�Ļ
	directOutput("ͻȻ!", 1);
	for (int i = 0; i < 3; ++i) {
		putImg(0, 0, 720, 480, "./PictureResource/white.png", 0);
		Sleep(100);
		putImg(0, 0, 720, 480, "./PictureResource/black.png", 0);
		Sleep(100);
	}
	setbkcolor(BLACK);
	clean();

	putImg(0, 0, 720, 360, "./PictureResource/CG/2.png", 0);
	streamOutput("�����Ļ��ʼ��˸!!! (Ӳ����˸)", 10, 2);
	streamOutput("���......����......׹��......", 50, 2);
	directOutput("ž��!!!", 1);
	streamOutput("�������һ������׵�ƽ̨...(û�ĵ��׹���)", 10, 2);
	clean();

	putImg(0, 0, 720, 360, "./PictureResource/CG/3.png", 0);
	streamOutput("��������, �㷢���Լ�������������һ��ĳ���.", 10, 2);
	streamOutput("ǽ�ڷǳ��⻬, ������һ˿���ڵĺۼ�.", 10, 2);
	streamOutput("����ֻ�ܳ����������ϵ���Ϸ��...!", 10, 1);
	directOutput("(�����������ΪĿ������ж�)", -1);

	// ��һ��
	streamOutput("WASD�ƶ�, Q��������, R���¿�ʼ.", 10, 2);
	engine->runGameSokoban();
	clean();

	putImg(0, 0, 720, 360, "./PictureResource/CG/15.png", 0);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("���������ӷ��õ���ȷ��λ�ú�,", 10, 1);
	streamOutput("�����ǽ�ڶ��������ֳ����ص�ʯ��...", 10, 1);

	// ��һ�ط�֧
	temp = 0;
	do
	{
		clean();
		putImg(0, 0, 720, 360, "./PictureResource/CG/20.png", 0);
		choice = choiceOutput("�����:", { "�۲����ʯ��", "�۲��Ҳ�ʯ��", "�����۲�" });
		switch (choice)
		{
		case 1:
			if (temp)
			{
				streamOutput("����ǿ�.", 10, 1);
				break;
			}
			putImg(0, 0, 720, 360, "./PictureResource/CG/4key.png", 0);
			streamOutput("���ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ����������׵����.", 10, 1);
			streamOutput("�ڲ�Զ���İ��, Ư���Ž�ɫ��Կ��...", 10, 1);
			temp = 1;
			break;

		case 2:
			putImg(0, 0, 720, 360, "./PictureResource/CG/5door.png", 0);
			streamOutput("�Ҳ�ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ΢����ŷ����ս���...", 10, 1);
			streamOutput("�����������һ����ƽ̨.", 10, 1);
			break;

		default:
			break;
		}
		clearRect(BLACK);
	} while (choice != 3);
	clean();

	// �ڶ��ر�Ļ
	putImg(0, 0, 720, 360, "./PictureResource/CG/6b.png", 0);
	streamOutput("����ǿ�, �ұ�����...", 10, 1);
	streamOutput("������ֻ�����ұ���..?", 10, 1);
	streamOutput("����㲻�������������Ļ�.(�㲻����)", 10, 1);
	streamOutput("������ת����������ȥ......", 10, 1);
	streamOutput("......", 60, 2);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("ʯ���ھ����йر�.", 10, 1);
	clean();

	// �ڶ��ط�֧
	putImg(0, 0, 720, 360, "./PictureResource/CG/6.png", 0);
	clearRect(BLACK);
	streamOutput("������������µ�����...", 10, 1);
	streamOutput("���߾�ͷ��һ���Ǳ�. emmm�趨��һ��Ǳ�������ҪԿ�ײ��ܽ���...", 10, 1);
	streamOutput("��ǰ��ȥ,��Զ���İ��Ư����һ��\"���˷���\"...", 10, 1);
	choice = choiceOutput("�����:", { "�ϴ�����", "�Ӷ�����", "�۲췽��", "��������" });
	switch (choice)
	{
	case 1:
		streamOutput("���ϴ�����,", 10, 2);
		putImg(0, 0, 720, 480, "./PictureResource/white.png", 0);
		Sleep(60);
		putImg(0, 0, 720, 480, "./PictureResource/black.png", 0);
		streamOutput("��ĵ��˼׹���...", 100, 1);
		streamOutput("���� ��.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		streamOutput("��, ��������, �Ͼ��Թ�CT��̧ͷ.", 10, 1);
		streamOutput("����ǰ��, �㷢����һ�����.", 10, 1);
		clean();

		choice = choiceOutput("�����:", { "�Ӷ���������ǰ��", "�۲�ӵ���Χ" });
		switch (choice)
		{
		case 1:
			streamOutput("��������.", 100, 2);
			putImg(0, 0, 720, 480, "./PictureResource/white.png", 0);
			Sleep(60);
			putImg(0, 0, 720, 480, "./PictureResource/black.png", 0);
			streamOutput("��������·ƽ��ǰ�����������.", 60, 1);
			streamOutput("���� ��.", 200, -1);
			clean();
			delete engine;
			goto BEGINING;
		case 2:
			//
			streamOutput("�ӵ׺�����һ��ͨ��?", 10, 1);
			streamOutput("����...", 10, 1);
			streamOutput("����Ȼ��̫��ֱ����������...(��ĵ��׹���)", 10, 1);
			streamOutput("����, ��ȥ�����˷����...", 10, 1);
			clean();
			break;
		default:
			break;
		}
	case 3:
		clean();
		putImg(0, 0, 720, 360, "./PictureResource/CG/7.png", 0);
		streamOutput("ƽƽ����ķ����.", 10, 1);
		streamOutput("�㶢�ŷ�����������, ���⻹��ƽƽ����ķ����.", 10, 1);
		streamOutput("�����ס�����ĳ嶯.", 10, 1);
		clean();
		streamOutput(".................", 80, 3);
	case 4:
		clean();
		putImg(0, 0, 720, 360, "./PictureResource/CG/7.png", 0);
		streamOutput("�㶢�ŷ�����������, ���Ǻ������...", 10, 1);
		streamOutput("����߶����ٿ̼��߰ߣ����ϵİ���Ҳƽ�������.", 10, 1);
		streamOutput("�ӸǶ���΢΢͸����ɫ�Ĺ�â----���۶�����.", 10, 1);
		streamOutput("��һ˲��, ���������÷��������˱���.", 10, 1);
		streamOutput("��һ�̻�������...", 10, 1);
		streamOutput("������һ����, �����, �����÷���:", 60, 1);
		streamOutput("���ϵ�����һ��ң����һ���ķ�����.", 10, 1);
		clean();
		break;
	default:
		break;
	}
	clean();

	// �ڶ���
	putImg(0, 0, 720, 360, "./PictureResource/CG/8.png", 0);
	streamOutput("����Ӵ��������ӵ�һ˲��!", 10, 1);
	streamOutput("����Ժ��������˿������ʥ������...", 10, 1);
	streamOutput("���������:", 10, 1);
	streamOutput("\"�������ƹ��ŷ��������!\"", 10, 2);
	streamOutput("\"���Ǳ����֮�������ġ����򷽿项�����׹��ʱ,\"", 10, 2);
	streamOutput("\"Ψ��̤�ϡ�����֮�ס�,���ܻ�á�����̽᡹��Ȩ��!\"", 10, 2);
	streamOutput("\"����������ƫ��ʥ�ۣ��󴥽��ɵ���λ...\"", 10, 2);
	streamOutput("\"������֮ͫ�������Ȼ����! \"", 10, 2);
	streamOutput("\"���齫��ɲ�Ǳ���Ϊ�ǳ�����ʱ�յ��ѷ����ɣ����������޷�����!\"", 10, 2);
	streamOutput("\"----���ˡ�����ħ�񡹵�����! \"", 10, 2);
	streamOutput("\"Ψ�о�׼������ط���֮��, ������������������˲���----����������!\"", 10, 2);
	streamOutput("\"�ǻ۵���ʿ!�������˵İ�ť!!����ͨ���Ǳ��Ľ��ݰ�!!!\"", 10, 2);
	directOutput("\n(��̽��\"���������\"ΪĿ������ж�)\n", -1);
	clean();

	streamOutput("WASD�ƶ�����ת����, Q��������, R���¿�ʼ.", 10, 2);
	engine->runGameTetris();
	clean();

	// �ڶ��ط�֧
	putImg(0, 0, 720, 360, "./PictureResource/CG/9.png", 0);//
	streamOutput("��ɹ���!!! ", 10, 1);
	streamOutput("��������, ����֮��, �Ի�����Ӱ...", 10, 1);
	streamOutput("������������ǻ�, �κ�����ļ׹���!(��������̨������)", 10, 1);
	choice = choiceOutput("�����:", { "����̨�׶�", "������̨����", "����̨�׽�" });
	switch (choice)
	{
	case 1:
		putImg(0, 0, 720, 480, "./PictureResource/white.png", 0);
		Sleep(60);
		putImg(0, 0, 720, 480, "./PictureResource/black.png", 0);
		clean();
		streamOutput("row~~~~~~bomb!", 60, 1);
		streamOutput("���ƺ��߹����Լ��ĵ�����, ���������̨����...", 10, 1);
		streamOutput("���� ��.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		streamOutput("�������˰����. ����ڲ�ȷʵ�и���֪������ͨ��.", 10, 1);
		break;
	case 3:
		streamOutput("ڤڤ��, ���ƺ����鵽��ʧ�ظ�...", 10, 1);
		streamOutput("ʧ�ظк�ǿ��...", 10, 1);
		putImg(0, 0, 720, 480, "./PictureResource/white.png", 0);
		Sleep(60);
		putImg(0, 0, 720, 480, "./PictureResource/black.png", 0);
		streamOutput("......", 100, 1);
		streamOutput("���С��ֺ�����˵�һ��̨����.", 100, 1);
		streamOutput("���� ��.", 200, 0);
		clean();
		delete engine;
		goto BEGINING;
	default:
		break;
	}
	temp = 0;
	do
	{
		clean();
		putImg(0, 0, 720, 360, "./PictureResource/CG/9.png", 0);
		choice = choiceOutput("�����:", { "���ͨ��", "ǰ���Ǳ�", "��������ȥ" });
		switch (choice)
		{
		case 1:
			putImg(0, 0, 720, 360, "./PictureResource/CG/27.png", 0);
			streamOutput("ͨ���ڵ�����һ��ֽ��:", 10, 1);
			streamOutput("��ͨ������ð����!", 10, 1);
			streamOutput("���������ͨ��, �·�����ĳ���, ��������, ������ֻ��!", 10, 2);
			streamOutput("�����ȥ!��----���˵�ֱ���������˻��.", 10, 2);
			streamOutput("����С��!��", 10, 1);
			streamOutput("���ǶȲ���, ��Ῠ������ļз���, ��ɺ��˿��еġ�ͨ����Թ�项.", 10, 2);
			streamOutput("���ٶ�̫��, �ᱻ�����涢��, �������ʳ��ԥ�ߵĽ�ָͷ.", 10, 2);
			streamOutput("�����Ʋ�˧...��Ǹ, ��������������, ��˧���˲�����ͨ��.", 10, 2);
			streamOutput("�������ɹ�----��", 10, 1);
			streamOutput("�㽫�������궴��ʦ���ɾ�!", 10, 1);
			streamOutput("��----Ҫ������? ������������뷢��!��", 10, 1);
			streamOutput("(�ײ�С��: ������, ��ͨ����ͨ���Ǽʰ�ȫ��֤,)", 10, 2);
			streamOutput("(ʧ�ܵ��궴��99%�����Ż�����...)", 10, 1);
			streamOutput("(...���.)", 100, 1);
			break;
		case 2:
			temp++;
			if (temp == 1)
			{
				clean();
				putImg(0, 0, 720, 360, "./PictureResource/CG/21.png", 0);
				streamOutput("�������˳Ǳ������...", 10, 1);
				streamOutput("�㷢�ֳǱ�����ڴ���һ����.", 10, 1);
				clean();
				putImg(0, 0, 720, 360, "./PictureResource/CG/10.png", 0);
				streamOutput("���Ϲ��Ž����������.", 10, 1);
				streamOutput("���Ĺ������Ԩ�е�Կ�����һ��...", 10, 1);
			}
			else if (temp > 1 && temp < 6)
			{
				clean();
				putImg(0, 0, 720, 360, "./PictureResource/CG/10.png", 0);
				streamOutput("���ȥͨ������.", 10, 1);
			}
			else if (temp == 6)
			{
				clean();
				putImg(0, 0, 720, 360, "./PictureResource/CG/10.png", 0);
				streamOutput("����ô����...", 10, 1);
				streamOutput("�㲻�������Ű�..?", 10, 1);
				streamOutput("............", 100, 2);
				streamOutput("Ҫ��, ������?", 10, 1);
				srand(static_cast<unsigned int>(time(nullptr)));
				int seed = rand() % 5;
				if (seed == 0)
				{
					streamOutput("��ȥ, ������ҿ���...", 10, 1);
					temp = 0;
					goto BOSS;
				}
				else
				{
					streamOutput("����˿����.", 10, 1);
					streamOutput("�㻹��ȥͨ����.", 10, 1);
				}
			}
			else
			{
				clean();
				putImg(0, 0, 720, 360, "./PictureResource/CG/21.png", 0);
				streamOutput("������. û�õ�.", 10, 1);
				streamOutput("���ȥͨ������.", 10, 1);
			}
			break;
		case 3:
			streamOutput("�㳢������ȥ...", 10, 1);
			streamOutput("............", 100, 1);
			streamOutput("����ÿ�����...", 60, 1);
			break;
		default:
			break;
		}
		clearRect(BLACK);
	} while (choice != 1);
	clean();

	// �����ر�Ļ
	putImg(0, 0, 720, 360, "./PictureResource/CG/11.png", 0);
	streamOutput("����ͨ��, ����������ڵľ���...", 10, 1);
	clean();
	putImg(0, 0, 720, 360, "./PictureResource/CG/22.png", 0);
	streamOutput("ֱ��������, ����������ʱ��������Ԩ����մ������.", 10, 1);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("���̤�뾮��, ���㴫�����Ƶľ���.", 10, 1);
	streamOutput("����, ���²��ò��Ը����ʯǽ��.", 10, 1);
	streamOutput("......", 60, 1);
	streamOutput("��������ԥ.", 10, 1);
	streamOutput("����ȴ�ٶ���������ĵ���...", 10, 1);
	clean();
	putImg(0, 0, 720, 360, "./PictureResource/CG/8.png", 0);
	streamOutput("(����������ĵ���)", 10, 1);
	directOutput("\n(���õ�Կ��ȥ���Ǳ�ΪĿ������ж�)\n", -1);
	clean();

	// ������
	streamOutput("WASD����ʯ�ߵ��˶�, Q��������, R���¿�ʼ.", 10, 2);
	engine->runGameSnake();
	clean();

	// ���Ĺر�Ļ
	putImg(0, 0, 720, 360, "./PictureResource/CG/20.png", 0);
	streamOutput("���ѵ�Ծ��ʯ�ź�, ��Ȼ...", 10, 1);
	streamOutput("�����������ʱ�Ǹ������ӵĳ���!", 10, 1);
	streamOutput("����...�ƺ�������Ĳ��ֲ�̫һ��..?", 10, 1);
	streamOutput("��ܲ�����ô����! (���ʱ��Ҫװɵ.JPG)", 10, 1);
	directOutput("\n(���ٴο����Ҳ�ʯ��ΪĿ������ж�)\n", -1);
	clean();

	// ���Ĺ�
	streamOutput("WASD�ƶ�����, Q��������, R���¿�ʼ.", 10, 1);
	engine->runGameSokoban(); // �ȴ�cv
	clean();

	// ���Ĺؽ�Ļ
	putImg(0, 0, 720, 360, "./PictureResource/CG/6b.png", 0);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("����һЩ��ϸ��, ʯ�����ڿ�ʼŲ��.", 10, 1);
	streamOutput("......", 60, 1);
	streamOutput("���ٴ���������µ�����.", 10, 1);
	choices = { "�۲�ʯ��", "�۲����", "�۲����˷���", "�۲������Χ", "ǰ�����񳤽�" };
	do
	{
		clean();
		putImg(0, 0, 720, 360, "./PictureResource/CG/6b.png", 0);
		choice = choiceOutput("�����:", choices);
		switch (choice)
		{
		case 1:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/19.png", 0);
			streamOutput("ʯ����ģ���ؿ���һ����:", 10, 1);
			streamOutput("JuFireStudio", 10, 1);
			streamOutput("��...�ѵ��Ƿ�α��ʶ��...", 10, 1);
			break;
		case 2:
			streamOutput("�����ε��ɫ, ������ǧֽ��...(bushi)", 10, 1);
			break;
		case 3:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/7.png", 0);
			streamOutput("ƽƽ����ķ����...", 10, 1);
			streamOutput("������ע�ӹ�����.��������Ȼ��ƽƽ����ķ����...", 10, 1);
			streamOutput("......", 60, 1);
			streamOutput("��������...", 10, 1);
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/18.png", 0);
			streamOutput("����������ʮ��ķ�˪, ��������ʱ�������ķ������...", 10, 1);
			streamOutput("��һֱû��, ȴ������˺ܶ�.", 10, 1);
			streamOutput("��ʱ�����˰�. �ӵ�����Ϸ�ոյ���, �����ķ���ʢ��.", 10, 1);
			break;
		case 4:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/25.png", 0);
			streamOutput("����ʵ����. ������Minecraft���ʸ�.", 10, 1);
			streamOutput("����Ժ����ƺ����ֳ��ƻ�, ľ��, ��...", 10, 1);
			streamOutput("�������ͯ����...", 10, 1);
			break;
		default:
			break;
		}
		clearRect(BLACK);
	} while (choice != 5);
	clean();

	// ����ر�Ļ
	putImg(0, 0, 720, 360, "./PictureResource/CG/9.png", 0);
	streamOutput("����Ϥ�Ľ���...", 10, 1);
	choices = { "�۲�ͨ�����", "�۲�̨��", "�۲����еķ���", "�۲�Ǳ�����", "����Ǳ�" };
	do
	{
		clean();
		choice = choiceOutput("�����:", choices);
		switch (choice)
		{
		case 1:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/19.png", 0);
			streamOutput("JuFireStudio...", 10, 1);
			streamOutput("(�߻�����)", 10, 1);
			break;
		case 2:
			streamOutput("�͵���������ͬ������ط緽��.", 10, 1);
			streamOutput("�������ѵ�����Ϸ��������ת�۵���˻���.", 10, 1);
			break;
		case 3:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/18.png", 0);
			streamOutput("�������е����, һ�������Ǽ�Ӳ�Ľ�������.", 10, 1);
			streamOutput("������һЩ��ɫ�İ���, ��������.", 10, 1);
			break;
		case 4:
			clean();
			putImg(0, 0, 720, 360, "./PictureResource/CG/10.png", 0);
			streamOutput("ʯ�ƵĴ���.", 10, 1);
			streamOutput("���Ϲ��Ž����������. ��â�����е�Կ�����һ��.", 10, 1);
			break;
		default:
			break;
		}
		clearRect(BLACK);
	} while (choice != 5);
	clean();

	// BOSS �ؿ�
	streamOutput("�����������һ����ǰ...", 10, 1);
BOSS:
	clean();
	putImg(0, 0, 720, 360, "./PictureResource/CG/23.png", 0);
	streamOutput("�������˵:", 10, 1);
	streamOutput("\"�ǻ۵���ʿ!���񹧺���ĵ���.\"", 10, 1);
	streamOutput("\"�Ǳ�������������.\"", 10, 1);
	streamOutput("\"�������, ��Ϳ��Դ��������ף���ص���ʵ!\"", 10, 1);
	clean();
	putImg(0, 0, 720, 360, "./PictureResource/CG/28.png", 0);
	streamOutput("����׼��, ����ǰ����������...", 10, 1);
	directOutput("\n(���������ʼ����)\n", -1);
	clean();

	streamOutput("WASD�ƶ����, Q��������, R���¿�ʼ.", 10, 1);
	engine->runGamePacman();
	clean();

	// ��Ϸ����
	putImg(0, 0, 720, 360, "./PictureResource/CG/18.png", 0);
	streamOutput("�����������һ�Ŷ��ӵ�ɲ��!", 10, 1);
	streamOutput("�������.", 10, 1);
	streamOutput("�����ڷ�������ǰ, ������δ�ϳɵ�2048...", 10, 1);
	clean();

	// �����
	streamOutput("(�����ҵ��뷨��, ����������һ�����һ���ϳ�2048�Ĳо�, �ϳ�2048������Ϸ)", 10, -1);

	delete engine;
	return 0;
}
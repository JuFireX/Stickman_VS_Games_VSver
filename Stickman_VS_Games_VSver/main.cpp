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

static int x = 10, y = 300;
static int BASIC_X = 10, BASIC_Y = 360, BASIC_H=20;
Engine* engine = new Engine();
// ת��GBK����Ϊ���ַ���
wstring gbk_to_wstring(const string &str)
{
	int len = MultiByteToWideChar(936, 0, str.c_str(), -1, NULL, 0); // 936=GBK
	wstring wstr(len, L'\0');
	MultiByteToWideChar(936, 0, str.c_str(), -1, &wstr[0], len);
	// ȥ��ĩβ��\0
	if (!wstr.empty() && wstr.back() == L'\0')
		wstr.pop_back();
	return wstr;
}

// ���� cls
void clean()
{
	//Sleep(2000);
	cleardevice();
	y = BASIC_Y;
}

// �ȴ��û����� pause
void pause(int timeout)
{
	flushmessage(-1);
	if (timeout == -1)
	{
		y += BASIC_H;
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
void streamOutput(const string text, int speed, int timeout, int color = 0xffffff)
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

	if (y >= 460)
	{
		y = BASIC_Y;
		cleardevice();
	}
	ExMessage msg;
	for (wchar_t wc : wtext)
	{
		int a = speed;
		out += wc;
		outtextxy(x, y, out.c_str());
		FlushBatchDraw();
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == 'Y')
				{
					a = 0;
					break;
				}
			}
		}
		flushmessage();
		Sleep(a);
	}

	y += BASIC_H;
	pause(timeout);
}

// �������
void directOutput(const string text, int timeout, int color = 0xffffff)
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

	if (y >= 460)
	{
		y = BASIC_Y;
		cleardevice();
	}

	outtextxy(x, y, wtext.c_str());
	FlushBatchDraw();

	y += BASIC_H;
	pause(timeout);
}

void clearRect(int top, COLORREF color)
{
	Sleep(2000);
	setfillcolor(color);
	solidrectangle(720, top, 0, 480);
	y = BASIC_Y;
}
// ���ѡ��
int choiceOutput(const string &output, const vector<string> &choices, int basec = WHITE, int selectc = RED)
{
	int select = 0;
	int n = (int)choices.size();
	int base_x = 480, base_y = BASIC_Y - (n+1)*BASIC_H, line_h = BASIC_H;
	streamOutput(output, 10, 0, basec);

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
					return select + 1;
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
void putImg(int x, int y,int width,int height,string path,int timeout)
{
	IMAGE temp;
	std::wstring wpath = std::wstring(path.begin(), path.end());
	loadimage(&temp, wpath.c_str(),width , height);
	engine->putimage_alpha(x, y, &temp, 255);
	FlushBatchDraw();
	pause(timeout);
}

void initGameCli(int count)
{
	system("title �����VS������Ϸ");
	system("mode con cols=120 lines=30");
	system("cls");
	if (count == 1)
		directOutput("Ӵ! �����ʵ�һ��Ŀ��� :P", 1);
	else if (count == 2)
		directOutput("Ŷ��? hello, again? ", 1);
	else if (count == 5)
		directOutput("��? ���ڸ���?? ", 1);
	else
		directOutput("������~~", 1);
	pause(0);
}

// ������
int main()
{
	int count = 1;
	int temp = 0;
BEGINING:
	
	vector<string> choices;
	int choice = 0;
	engine->initGame();
	setbkcolor(WHITE);
	// ���±�Ļ
	initGameCli(count++);
	streamOutput("��������, �������ĵ���2048...", 50, 0);
	directOutput("(������2048ΪĿ������ж�)", -1);

	// ����
	streamOutput("WASD�ƶ�, Q��������.", 10, 0);
	engine->runGame2048();
	clean();

	// ��һ�ر�Ļ
	directOutput("ͻȻ!", 1);
	for (int i = 0; i < 3; ++i) {
		putImg(0, 0, 720, 360, "./PictureResource/white.png", 0);
		putImg(0, 0, 720, 360, "./PictureResource/black.png", 0);
		Sleep(100);
	}
	streamOutput("�����Ļ��ʼ��˸!!! (��Ҫ����������)", 10, 0,WHITE);
	streamOutput("���..����...׹��......", 50, 2,WHITE);
	setbkcolor(BLACK);
	directOutput("ž��!!!", 1);
	streamOutput("�������һ������׵�ƽ̨...(û�ĵ��׹���)", 10, 0);
	streamOutput("��������, �㷢���Լ�������������һ��ĳ���.", 10, 0);
	streamOutput("ǽ�ڷǳ��⻬, ������һ˿���ڵĺۼ�.", 10, 0);
	streamOutput("����ֻ�ܳ����������ϵ���Ϸ��...!", 10, 0);
	directOutput("(�����������ΪĿ������ж�)", -1);

	// ��һ��
	streamOutput("WASD�ƶ�, Q��������, R���¿�ʼ.", 10, 0);
	engine->runGameSokoban();
	clean();
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("���������ӷ��õ���ȷ��λ�ú�,", 10, 0);
	streamOutput("�����ǽ�ڶ������ƿ��˺��ص�ʯ��...", 10, 0);
	temp = 0;
	// ��һ�ط�֧
	do
	{
		choice = choiceOutput("�����:", {"�۲����ʯ��", "�۲��Ҳ�ʯ��", "�����۲�"});
		switch (choice)
		{
		case 1:
			if (temp)
			{
				streamOutput("����ǿ�.", 10, 0);
				break;
			}
			streamOutput("���ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ����������׵����.", 10, 0);
			streamOutput("�ڲ�Զ���İ��, Ư���Ž�ɫ��Կ��...", 10, 0);
			temp = 1;
			break;

		case 2:
			streamOutput("�Ҳ�ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ΢����ŷ����ս���...", 10, 0);
			streamOutput("�����������һ����ƽ̨.", 10, 0);
			break;

		default:
			break;
		}
		clearRect(300,0x00000);
	} while (choice != 3);
	clean();

	// �ڶ��ر�Ļ
	streamOutput("������ֻ��ǰ�������ƽ̨��..?", 10, 0);
	streamOutput("����㲻�������������Ļ�.(�㲻����)", 10, 0);
	streamOutput("������ת����������ȥ......", 10, 0);
	streamOutput("......", 60, 1);
	streamOutput("......", 60, 1);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("ʯ���ھ����йر�.", 10, 0);
	clean();

	// �ڶ��ط�֧
	streamOutput("������������µ�����...", 10, 0);
	streamOutput("���߾�ͷ��һ���Ǳ�. emmm�趨��һ��Ǳ�������ҪԿ�ײ��ܽ���...", 10, 0);
	streamOutput("��ǰ��ȥ,��Զ���İ��Ư����һ��\"���˷���\"...", 10, 0);
	clean();
	choice = choiceOutput("�����:", {"�ϴ�����", "�Ӷ�����", "�۲췽��", "��������"});
	switch (choice)
	{
	case 1:
		streamOutput("���ϴ�����,", 10, 0);
		streamOutput("��ĵ��˼׹���...", 100, 1);
		streamOutput("���� ��.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		clean();
		streamOutput("��, ��������, �Ͼ��Թ�CT��̧ͷ.", 10, 0);
		streamOutput("����ǰ��, �㷢����һ�����.", 10, 0);
		choice = choiceOutput("�����:", {"�Ӷ���������ǰ��", "�۲�ӵ���Χ"});
		switch (choice)
		{
		case 1:
			streamOutput("��������.", 100, 1);
			streamOutput("��������·ƽ��ǰ�����������.", 60, 1);
			streamOutput("���� ��.", 200, -1);
			clean();
			delete engine;
			goto BEGINING;
		case 2:
			streamOutput("�ӵ׺�����һ��ͨ��?", 10, 0);
			streamOutput("����...", 10, 0);
			streamOutput("����Ȼ��̫��ֱ����������...(��ĵ��׹���)", 10, 0);
			streamOutput("����, ��ȥ�����˷����...", 10, 0);
			clean();
			break;
		default:
			break;
		}
	case 3:
		streamOutput("ƽƽ����ķ����.", 10, 0);
		streamOutput("�㶢�ŷ������������, ���⻹��ƽƽ����ķ����.", 10, 0);
		streamOutput("�����ס�����ĳ嶯.", 10, 0);
		streamOutput(".......", 100, 3);
		clean();
	case 4:
		streamOutput("�㶢�ŷ������������, ���Ǻ������...", 10, 0);
		streamOutput("����߶����ٿ̼��߰ߣ����ϵİ���Ҳƽ��������.", 10, 0);
		streamOutput("�ӸǶ���΢΢͸����ɫ�Ĺ�â----���۶�����.", 10, 0);
		streamOutput("��һ˲��, ���������÷��������˱���.", 10, 0);
		streamOutput("��һ�̻�������...", 10, 0);
		streamOutput("������һ����, �����, �����÷���:", 60, 1);
		streamOutput("���ϵ�����һ��ң����һ���ķ�����.", 10, 0);
		clean();
		break;
	default:
		break;
	}

	// �ڶ���
	streamOutput("����Ӵ��������ӵ�һ˲��!", 10, 0);
	streamOutput("����Ժ��������˿������ʥ������...", 10, 0);
	streamOutput("���������:", 10, 0);
	streamOutput("\"�������ƹ��ŷ��������!\"", 10, 0);
	streamOutput("\"���Ǳ����֮�������ġ����򷽿项�����׹��ʱ,\"", 10, 0);
	streamOutput("\"Ψ��̤�ϡ�����֮�ס�,���ܻ�á�����̽᡹��Ȩ��!\"", 10, 0);
	streamOutput("\"����������ƫ��ʥ�ۣ��󴥽��ɵ���λ...\"", 10, 0);
	streamOutput("\"������֮ͫ�������Ȼ����! \"", 10, 0);
	streamOutput("\"���齫��ɲ�Ǳ���Ϊ�ǳ�����ʱ�յ��ѷ����ɣ����������޷�����!\"", 10, 0);
	streamOutput("\"----���ˡ�����ħ�񡹵�����! \"", 10, 0);
	streamOutput("\"Ψ�о�׼������ط���֮��, ������������������˲���----������������!\"", 10, 0);
	streamOutput("\"�ǻ۵���ʿ!�������˵İ�ť!!����ͨ���Ǳ��Ľ��ݰ�!!!\"", 10, 0);
	directOutput("\n(��̽��\"���������\"ΪĿ������ж�)\n", -1);
	clean();

	streamOutput("WASD�ƶ�����ת����, Q��������, R���¿�ʼ.", 10, 0);
	engine->runGameTetris();
	clean();

	// �ڶ��ط�֧
	streamOutput("��ɹ���!!! ", 10, 0);
	streamOutput("��������, ����֮��, �Ի�����Ӱ...", 10, 0);
	streamOutput("������������ǻ�, �κ�����ļ׹���!(��������̨������)", 10, 0);

	choice = choiceOutput("�����:", {"����̨�׶�", "������̨����", "����̨�׽�"});
	switch (choice)
	{
	case 1:
		streamOutput("row~~~~~~bomb!", 60, 1);
		streamOutput("���ƺ��߹����Լ��ĵ�����, ���������̨����...", 10, 0);
		streamOutput("���� ��.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		clean();
		streamOutput("�������˰����. ����ڲ�ȷʵ�и���֪������ͨ��.", 10, 0);
		break;
	case 3:
		streamOutput("ڤڤ��, ���ƺ����鵽��ʧ�ظ�...", 10, 0);
		streamOutput("ʧ�ظк�ǿ��...", 10, 0);
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
		choice = choiceOutput("�����:", {"���ͨ��", "ǰ���Ǳ�", "��������ȥ"});
		switch (choice)
		{
		case 1:
			streamOutput("ͨ���ڵ�����һ��ֽ��:", 10, 0);
			streamOutput("��ͨ������ð����!", 10, 0);
			streamOutput("���������ͨ��, �·�����ĳ���, ��������, ������ֻ��!", 10, 0);
			streamOutput("�����ȥ!��----���˵�ֱ���������˻��.", 10, 0);
			streamOutput("����С��!��", 10, 0);
			streamOutput("���ǶȲ���, ��Ῠ������ļз���, ��ɺ��˿��еġ�ͨ����Թ�项.", 10, 0);
			streamOutput("���ٶ�̫��, �ᱻ�����涢��, �������ʳ��ԥ�ߵĽ�ָͷ.", 10, 0);
			streamOutput("�����Ʋ�˧...��Ǹ, ��������������, ��˧���˲�����ͨ��.", 10, 0);
			streamOutput("�������ɹ�----��", 10, 0);
			streamOutput("�㽫�������궴��ʦ���ɾ�!", 10, 0);
			streamOutput("��----Ҫ������? ������������뷢��!��", 10, 0);
			streamOutput("(�ײ�С��: ������, ��ͨ����ͨ���Ǽʰ�ȫ��֤,)", 10, 0);
			streamOutput("(ʧ�ܵ��궴��99%�����Ż�����...)", 10, 0);
			streamOutput("(...���.)", 60, 1);
			break;
		case 2:
			temp++;
			if (temp == 1)
			{
				streamOutput("�������˳Ǳ������...", 10, 0);
				streamOutput("�㷢�ֳǱ�����ڴ���һ����.", 10, 0);
				streamOutput("���Ϲ��Ž����������.", 10, 0);
				streamOutput("���Ĺ������Ԩ�е�Կ�����һ��...", 10, 0);
			}
			else if (temp > 1 && temp < 6)
			{
				streamOutput("���ȥͨ������.", 10, 0);
			}
			else if (temp == 6)
			{
				streamOutput("����ô����...", 10, 0);
				streamOutput("�㲻�������Ű�..?", 10, 0);
				streamOutput("......", 100, 1);
				streamOutput("......", 100, 1);
				streamOutput("Ҫ��, ������?", 10, 0);
				srand(static_cast<unsigned int>(time(nullptr)));
				int seed = rand() % 5;
				if (seed == 0)
				{
					streamOutput("��ȥ, ������ҿ���...", 10, 0);
					temp = 0;
					goto BOSS;
				}
				else
				{
					streamOutput("����˿����.", 10, 0);
					streamOutput("�㻹��ȥͨ����.", 10, 0);
				}
			}
			else
			{
				streamOutput("������. û�õ�.", 10, 0);
				streamOutput("���ȥͨ������.", 10, 0);
			}
			break;
		case 3:
			streamOutput("�㳢������ȥ...", 10, 0);
			streamOutput("......", 60, 1);
			streamOutput("......", 60, 1);
			streamOutput("����ÿ�����...", 60, 1);
			break;
		default:
			break;
		}
		clearRect(300,0x00000);
	} while (choice != 1);
	clean();

	// �����ر�Ļ
	streamOutput("����ͨ��, ����������ڵľ���...", 10, 0);
	streamOutput("ֱ��������, ����������ʱ��������Ԩ����մ������.", 10, 0);
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("���̤�뾮��, ����㴫�����Ƶľ���.", 10, 0);
	streamOutput("����, ���²��ò��Ը����ʯǽ��.", 10, 0);
	streamOutput("......", 60, 1);
	streamOutput("��������ԥ.", 10, 0);
	streamOutput("����ȴ�ٶ���������ĵ���...", 10, 0);
	streamOutput("(����������ĵ���,�����һ�û�����ô������Ϸ����.. ���ڳ���Ҫ��Ҫ�޸�,�д���ȶ)", 10, 0);
	directOutput("\n(���õ�Կ��ȥ���Ǳ�ΪĿ������ж�)\n", -1);
	clean();

	// ������
	streamOutput("WASD����ʯ�ߵ��˶�, Q��������, R���¿�ʼ.", 10, 0);
	engine->runGameSnake();
	clean();

	// ���Ĺر�Ļ
	streamOutput("���ѵ�Ծ��ʯ�ź�, ��Ȼ...", 10, 0);
	streamOutput("�����������ʱ�Ǹ������ӵĳ���!", 10, 0);
	streamOutput("����...�ƺ�������Ĳ��ֲ�̫һ��..?", 10, 0);
	streamOutput("��ܲ�����ô����! (���ʱ��Ҫװɵ.JPG)", 10, 0);
	directOutput("\n(���ٴο����Ҳ�ʯ��ΪĿ������ж�)\n", -1);

	// ���Ĺ�
	streamOutput("WASD�ƶ�����, Q��������, R���¿�ʼ.", 10, 0);
	engine->runGameSokoban(); // �ȴ�cv
	clean();

	// ���Ĺؽ�Ļ
	streamOutput("��¡~~~~~~~~~~", 100, 2);
	streamOutput("����һЩ��ϸ��, ʯ�����ڿ�ʼŲ��.", 10, 0);
	streamOutput("......", 60, 1);
	streamOutput("���ٴ���������µ�����.", 10, 0);
	do
	{
		choices = { "�۲�ʯ��", "�۲����", "�۲����˷���", "�۲������Χ", "ǰ�����񳤽�" };
		choice = choiceOutput("�����:", choices);
		switch (choice)
		{
		case 1:
			streamOutput("ʯ����ģ���ؿ���һ����:", 10, 0);
			streamOutput("JuFireStudio", 10, 0);
			streamOutput("��...�ѵ��Ƿ�α��ʶ��...", 10, 0);
			break;
		case 2:
			streamOutput("�����ε��ɫ, ������ǧֽ��...(bushi)", 10, 0);
			break;
		case 3:
			streamOutput("ƽƽ����ķ����...", 10, 0);
			streamOutput("������ע�ӹ�����.��������Ȼ��ƽƽ����ķ����...", 10, 0);
			streamOutput("......", 60, 1);
			streamOutput("��������...", 10, 0);
			streamOutput("����������ʮ��ķ�˪, ��������ʱ�������ķ������...", 10, 0);
			streamOutput("��һֱû��, ȴ������˺ܶ�.", 10, 0);
			streamOutput("��ʱ�����˰�. �ӵ�����Ϸ�ոյ���, �����ķ���ʢ��.", 10, 0);
			break;
		case 4:
			streamOutput("����ʵ����. ������Minecraft���ʸ�.", 10, 0);
			streamOutput("����Ժ����ƺ����ֳ��ƻ�, ľ��, ��...", 10, 0);
			streamOutput("�������ͯ����...", 10, 0);
			break;
		default:
			break;
		}
		clearRect(300,0x00000);
	} while (choice != 5);
	clean();

	// ����ر�Ļ
	streamOutput("����Ϥ�Ľ���...", 10, 0);
	do
	{
		choices = { "�۲�ͨ�����", "�۲�̨��", "�۲����еķ���", "�۲�Ǳ�����", "����Ǳ�" };
		choice = choiceOutput("�����:", choices);
		switch (choice)
		{
		case 1:
			streamOutput("JuFireStudio...", 10, 0);
			streamOutput("(�߻�����)", 10, 0);
			break;
		case 2:
			streamOutput("�͵���������ͬ������ط緽��.", 10, 0);
			streamOutput("�������ѵ�����Ϸ��������ת�۵���˻���.", 10, 0);
			break;
		case 3:
			streamOutput("�������е����, һ�������Ǽ�Ӳ�Ľ�������.", 10, 0);
			streamOutput("������һЩ��ɫ�İ���, ��������.", 10, 0);
			break;
		case 4:
			streamOutput("ʯ�ƵĴ���.", 10, 0);
			streamOutput("���Ϲ��Ž����������. ��â�����е�Կ�����һ��.", 10, 0);
			break;
		default:
			break;
		}
		clean();
	} while (choice != 5);

	// BOSS �ؿ�
	streamOutput("�����������һ����ǰ...", 10, 0);
BOSS:
	streamOutput("�������˵:", 10, 0);
	streamOutput("\"�ǻ۵���ʿ!���񹧺���ĵ���.\"", 10, 0);
	streamOutput("\"�Ǳ�������������.\"", 10, 0);
	streamOutput("\"�������, ��Ϳ��Դ��������ף���ص���ʵ!\"", 10, 0);
	streamOutput("����׼��, ����ǰ����������...", 10, 0);
	directOutput("\n(���������ʼ����)\n", -1);

	streamOutput("WASD�ƶ����, Q��������, R���¿�ʼ.", 10, 0);
	engine->runGamePacman();
	clean();

	// ��Ϸ����
	streamOutput("�����������һ�Ŷ��ӵ�ɲ��!", 10, 0);
	streamOutput("�������.", 10, 0);
	streamOutput("�����ڷ�������ǰ, ������δ�ϳɵ�2048...", 10, 0);
	clean();

	// �����
	streamOutput("(�����ҵ��뷨��, ����������һ�����һ���ϳ�2048�Ĳо�, �ϳ�2048������Ϸ)", 10, -1);

	delete engine;
	return 0;
}
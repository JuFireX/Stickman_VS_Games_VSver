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

static int x = 10, y = 5;

// 转换GBK编码为宽字符串
wstring gbk_to_wstring(const string& str)
{
	int len = MultiByteToWideChar(936, 0, str.c_str(), -1, NULL, 0); // 936=GBK
	wstring wstr(len, L'\0');
	MultiByteToWideChar(936, 0, str.c_str(), -1, &wstr[0], len);
	// 去掉末尾的\0
	if (!wstr.empty() && wstr.back() == L'\0')
		wstr.pop_back();
	return wstr;
}

// 清屏 cls
void clean()
{
	cleardevice();
	y = 10;
}

// 等待用户输入 pause
void pause(int timeout)
{
	if (timeout == -1)
	{
		y += 20;
		if (y >= 450)
		{
			y = 10;
			cleardevice();
		}
		outtextxy(10, y, _T(">>>"));
		y += 20;

		FlushBatchDraw();
		ExMessage getmessage(BYTE filter = EX_KEY);
		getmessage();
	}
	else
	{
		Sleep(timeout * 1000); // 这里玩家无法跳过等待,需要修改逻辑
	}
}

// 模拟流式输出
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

	// 转码
	wstring wtext = gbk_to_wstring(text);
	wstring out;

	if (y >= 450)
	{
		y = 0;
		cleardevice();
	}

	for (wchar_t wc : wtext)
	{
		out += wc;
		outtextxy(x, y, out.c_str());
		FlushBatchDraw();
		Sleep(speed);
	}

	y += 20;
	pause(timeout);
}

// 整行输出
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

	// 转码
	wstring wtext = gbk_to_wstring(text);

	if (y >= 450)
	{
		y = 10;
		cleardevice();
	}

	outtextxy(x, y, wtext.c_str());
	FlushBatchDraw();

	y += 20;
	pause(timeout);
}

// 输出选择
int choiceOutput(const string& output, const vector<string>& choices, int basec = WHITE, int selectc = RED)
{
	int base_x = 5, base_y = y, line_h = 20;
	int select = 1;
	int n = (int)choices.size();
	streamOutput(output, 10, 0, basec);

	while (true)
	{
		for (int i = 1; i <= n; ++i)
		{
			wstring wstr = gbk_to_wstring(to_string(i) + " -> " + choices[i - 1]);
			int y_chioce = base_y + i * line_h;
			if (i == select)
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
		while (peekmessage(&msg)) // ?????????
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_DOWN || msg.vkcode == 'S')
				{
					select = ((select + n - 1) % n) + 1;
					continue;
				}
				else if (msg.vkcode == VK_UP || msg.vkcode == 'W')
				{
					select = ((select + 1) % n) + 1;
					continue;
				}
				else if (msg.vkcode == VK_RETURN || msg.vkcode == 'F')
				{
					y += 20 * n;
					return select;
				}
				else if ((msg.vkcode - '0') >= 1 && (msg.vkcode - '0') <= n)
				{
					select = (msg.vkcode - '0');
					y += 20 * n;
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

void initGameCli(int count)
{
	system("title 火柴人VS电子游戏");
	system("mode con cols=120 lines=30");
	system("cls");
	if (count == 1)
		directOutput("哟! 是新鲜的一周目玩家 :P", 1);
	else if (count == 2)
		directOutput("哦吼? hello, again? ", 1);
	else if (count == 5)
		directOutput("蛤? 你在干嘛?? ", 1);
	else
		directOutput("啧啧啧~~", 1);
	pause(1);
}

// 主流程
int main()
{
	int count = 1;
	int temp = 0;
BEGINING:
	Engine* engine = new Engine();
	vector<string> choices;
	int choice = 0;
	engine->initGame();
	setbkcolor(0x000000);
	cleardevice();

	// 序章报幕
	initGameCli(count++);
	streamOutput("你是再临, 正在无聊地玩2048...", 50, 1);
	directOutput("(以游玩2048为目标继续行动)", -1);

	// 序章
	streamOutput("WASD移动, Q跳过本关.", 10, 1);
	Sleep(1000);
	engine->runGame2048();
	clean();

	// 第一关报幕
	directOutput("突然!", 1);
	streamOutput("你的屏幕开始闪烁!!! (你要相信它闪了)", 10, 1);
	streamOutput("天崩..地裂...坠落......", 50, 2);
	directOutput("啪唧!!!", 1);
	streamOutput("你掉在了一处深不见底的平台...(没磕到甲沟炎)", 10, 1);
	streamOutput("环顾四周, 你发现自己来到了推箱子一般的场地.", 10, 1);
	streamOutput("墙壁非常光滑, 看不出一丝出口的痕迹.", 10, 1);
	streamOutput("看来只能尝试完成这古老的游戏了...!", 10, 1);
	directOutput("(以完成推箱子为目标继续行动)", -1);

	// 第一关
	streamOutput("WASD移动, Q跳过本关, R重新开始.", 10, 1);
	Sleep(1000);
	engine->runGameSokoban();
	clean();

	// 第一关分支
	streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
	streamOutput("当三个箱子放置到正确的位置后,", 10, 1);
	streamOutput("两侧的墙壁都缓缓移开了厚重的石门...", 10, 1);
	temp = 0;
	do
	{
		choice = choiceOutput("你决定:", { "观察左侧石门", "观察右侧石门", "结束观察" });
		switch (choice)
		{
		case 1:
			if (temp)
			{
				streamOutput("左边是坑.", 10, 1);
				break;
			}
			streamOutput("左侧石门的墙壁开始缓缓移开, 门外是深不见底的深坑.", 10, 1);
			streamOutput("在不远处的半空, 漂浮着金色的钥匙...", 10, 1);
			temp = 1;
			break;

		case 2:
			streamOutput("右侧石门的墙壁开始缓缓移开, 微光从门缝中照进来...", 10, 1);
			streamOutput("门外是马里奥一样的平台.", 10, 1);
			break;

		default:
			break;
		}
	} while (choice != 3);
	clean();

	// 第二关报幕
	streamOutput("看起来只能前往马里奥平台了..?", 10, 1);
	streamOutput("如果你不打算往坑里跳的话.(你不打算)", 10, 1);
	streamOutput("于是你转身向门外走去......", 10, 1);
	streamOutput("......", 60, 1);
	streamOutput("......", 60, 1);
	streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
	streamOutput("石门在巨响中关闭.", 10, 1);
	cleardevice();
	y = 10;

	streamOutput("你来到了马里奥的世界...", 10, 1);
	streamOutput("视线尽头是一座城堡. emmm设定上一般城堡都是需要钥匙才能进的...", 10, 1);
	streamOutput("向前走去,不远处的半空漂浮着一个\"幸运方块\"...", 10, 1);
	choice = choiceOutput("你决定:", { "上蹿下跳", "视而不见", "观察方块", "触碰方块" });
	clean();
	switch (choice)
	{
	case 1:
		streamOutput("你上蹿下跳,", 10, 1);
		streamOutput("你磕到了甲沟炎...", 100, 1);
		streamOutput("再临 卒.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		streamOutput("鹅, 不愧是你, 毕竟自古CT不抬头.", 10, 1);
		streamOutput("继续前进, 你发现了一个深坑.", 10, 1);
		choice = choiceOutput("你决定:", { "视而不见继续前进", "观察坑的周围" });
		switch (choice)
		{
		case 1:
			streamOutput("不愧是你.", 100, 1);
			streamOutput("你由于走路平视前方掉入了深坑.", 60, 1);
			streamOutput("再临 卒.", 200, -1);
			clean();
			delete engine;
			goto BEGINING;
		case 2:
			streamOutput("坑底好像有一个通道?", 10, 1);
			streamOutput("鹅鹅鹅...", 10, 1);
			streamOutput("你显然不太能直接往坑里跳...(会磕到甲沟炎)", 10, 1);
			streamOutput("蒜了, 回去摸幸运方块吧...", 10, 1);
			clean();
			break;
		default:
			break;
		}
	case 3:
		streamOutput("平平无奇的方块儿.", 10, 1);
		streamOutput("你盯着方块儿看了许久, 但这还是平平无奇的方块儿.", 10, 1);
		streamOutput("你克制住打开它的冲动.", 10, 1);
		streamOutput(".......", 100, 3);
	case 4:
		streamOutput("你盯着方块儿看了许久, 它们好像变了...", 10, 1);
		streamOutput("方块边儿不再刻迹斑斑，身上的凹陷也平整了许多.", 10, 1);
		streamOutput("从盖儿下微微透出金色的光芒----甜蜜而诱人.", 10, 1);
		streamOutput("有一瞬间, 你甚至觉得方块儿变成了宝箱.", 10, 1);
		streamOutput("这一刻还是来了...", 10, 1);
		streamOutput("你深吸一口气, 伸出手, 敲了敲方块:", 60, 1);
		streamOutput("地上掉落了一个遥控器一样的方盒子.", 10, 1);
		clean();
		break;
	default:
		break;
	}

	// 第二关
	streamOutput("当你接触到方盒子的一瞬间!", 10, 1);
	streamOutput("你的脑海里响起了空灵而神圣的声音...", 10, 1);
	streamOutput("码神告诉你:", 10, 1);
	streamOutput("\"方盒子掌管着方块的秘仪!\"", 10, 1);
	streamOutput("\"当那被虚空之力雕琢的「法则方块」自天穹坠下时,\"", 10, 1);
	streamOutput("\"唯有踏上「神铸之阶」,方能获得「永恒固结」的权能!\"", 10, 1);
	streamOutput("\"若愚者令其偏离圣痕，误触禁忌的虚位...\"", 10, 1);
	streamOutput("\"「湮灭之瞳」便会骤然睁开! \"", 10, 1);
	streamOutput("\"方块将在刹那崩解为星尘，被时空的裂缝吞噬，连悲鸣都无法残留!\"", 10, 1);
	streamOutput("\"----此乃「阶梯魔神」的试炼! \"", 10, 1);
	streamOutput("\"唯有精准契合天地法则之人, 方可聆听方块在凝固瞬间的----「真理共鸣」!\"", 10, 1);
	streamOutput("\"智慧的勇士!按下命运的按钮!!走上通往城堡的阶梯吧!!!\"", 10, 1);
	directOutput("\n(以探索\"方块的秘仪\"为目标继续行动)\n", -1);
	clean();

	streamOutput("WASD移动和旋转方块, Q跳过本关, R重新开始.", 10, 1);
	engine->runGameTetris();
	clean();

	// 第二关分支
	streamOutput("你成功了!!! ", 10, 1);
	streamOutput("方块落下, 阶梯之外, 皆化作泡影...", 10, 1);
	streamOutput("码神赞赏你的智慧, 治好了你的甲沟炎!(可以跳在台阶上了)", 10, 1);

	choice = choiceOutput("你决定:", { "跳到台阶顶", "跳到半台阶腰", "跳到台阶脚" });
	switch (choice)
	{
	case 1:
		streamOutput("row~~~~~~bomb!", 60, 1);
		streamOutput("你似乎高估了自己的弹跳力, 倒在最后半个台阶上...", 10, 1);
		streamOutput("再临 卒.", 200, -1);
		clean();
		delete engine;
		goto BEGINING;
	case 2:
		streamOutput("你跳到了半道儿. 深坑内部确实有根不知所至的通道.", 10, 1);
		break;
	case 3:
		streamOutput("冥冥中, 你似乎体验到了失重感...", 10, 1);
		streamOutput("失重感很强烈...", 10, 1);
		streamOutput("......", 100, 1);
		streamOutput("你的小脚趾磕在了第一节台阶上.", 100, 1);
		streamOutput("再临 卒.", 200, 0);
		clean();
		delete engine;
		goto BEGINING;
	default:
		break;
	}

	temp = 0;
	do
	{
		choice = choiceOutput("你决定:", { "钻进通道", "前往城堡", "尝试跳回去" });
		switch (choice)
		{
		case 1:
			streamOutput("通道口掉落着一张纸条:", 10, 1);
			streamOutput("钻通道的奇冒妙险!", 10, 1);
			streamOutput("这条幽邃的通道, 仿佛宇宙的肠子, 蜿蜒曲折, 暗藏玄只因!", 10, 1);
			streamOutput("「钻进去!」----命运的直觉在你耳边嘶吼.", 10, 1);
			streamOutput("「但小心!」", 10, 1);
			streamOutput("若角度不对, 你会卡在世界的夹缝里, 变成后人口中的「通道的怨灵」.", 10, 1);
			streamOutput("若速度太慢, 会被虚空蠕虫盯上, 它们最爱啃食犹豫者的脚指头.", 10, 1);
			streamOutput("若姿势不帅...抱歉, 这条是宇宙真理, 不帅的人不配钻通道.", 10, 1);
			streamOutput("「但若成功----」", 10, 1);
			streamOutput("你将解锁「钻洞大师」成就!", 10, 1);
			streamOutput("「----要试试吗? 赌上你的尊严与发型!」", 10, 1);
			streamOutput("(底部小字: 开拓者, 本通道已通过星际安全认证,)", 10, 1);
			streamOutput("(失败的钻洞者99%都活着回来了...)", 10, 1);
			streamOutput("(...大概.)", 60, 1);
			break;
		case 2:
			temp++;
			if (temp == 1)
			{
				streamOutput("你来到了城堡的入口...", 10, 1);
				streamOutput("你发现城堡的入口处有一扇门.", 10, 1);
				streamOutput("门上挂着金光闪闪的锁.", 10, 1);
				streamOutput("锁的光辉与深渊中的钥匙如出一辙...", 10, 1);
			}
			else if (temp > 1 && temp < 6)
			{
				streamOutput("你该去通道看看.", 10, 1);
			}
			else if (temp == 6)
			{
				streamOutput("你怎么还来...", 10, 1);
				streamOutput("你不会想砸门吧..?", 10, 1);
				streamOutput("......", 100, 1);
				streamOutput("......", 100, 1);
				streamOutput("要不, 你试试?", 10, 1);
				srand(static_cast<unsigned int>(time(nullptr)));
				int seed = rand() % 5;
				if (seed == 0)
				{
					streamOutput("我去, 真给你砸开了...", 10, 1);
					temp = 0;
					goto BOSS;
				}
				else
				{
					streamOutput("锁纹丝不动.", 10, 1);
					streamOutput("你还是去通道吧.", 10, 1);
				}
			}
			else
			{
				streamOutput("放弃吧. 没用的.", 10, 1);
				streamOutput("你该去通道看看.", 10, 1);
			}
			break;
		case 3:
			streamOutput("你尝试跳回去...", 10, 1);
			streamOutput("......", 60, 1);
			streamOutput("......", 60, 1);
			streamOutput("你觉得可能吗...", 60, 1);
			break;
		default:
			break;
		}
	} while (choice != 1);
	clean();

	// 第三关报幕
	streamOutput("穿过通道, 你置身于漆黑的井底...", 10, 1);
	streamOutput("直觉告诉你, 这里和你初来时遇见的深渊多少沾点亲戚.", 10, 1);
	streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
	streamOutput("你刚踏入井底, 身后便传来沉闷的巨响.", 10, 1);
	streamOutput("完了, 这下不得不对付这个石墙了.", 10, 1);
	streamOutput("......", 60, 1);
	streamOutput("你正在犹豫.", 10, 1);
	streamOutput("耳边却再度响起码神的低语...", 10, 1);
	streamOutput("(这里是码神的低语,但是我还没想好怎么设置游戏规则.. 至于程序要不要修改,有待商榷)", 10, 1);
	directOutput("\n(以拿到钥匙去往城堡为目标继续行动)\n", -1);
	clean();

	// 第三关
	streamOutput("WASD控制石蛇的运动, Q跳过本关, R重新开始.", 10, 1);
	engine->runGameSnake();
	clean();

	// 第四关报幕
	streamOutput("艰难的跃进石门后, 果然...", 10, 1);
	streamOutput("是你初次来到时那个推箱子的场地!", 10, 1);
	streamOutput("但是...似乎和最初的布局不太一样..?", 10, 1);
	streamOutput("你管不了这么多了! (这个时候要装傻.JPG)", 10, 1);
	directOutput("\n(以再次开启右侧石门为目标继续行动)\n", -1);

	// 第四关
	streamOutput("WASD移动箱子, Q跳过本关, R重新开始.", 10, 1);
	engine->runGameSokoban(); // 等待cv
	clean();

	// 第四关结幕
	streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
	streamOutput("费了一些脑细胞, 石门终于开始挪动.", 10, 1);
	streamOutput("......", 60, 1);
	streamOutput("你再次来到马里奥的世界.", 10, 1);
	choices = { "观察石门", "观察天空", "观察幸运方块", "观察深坑周围", "前往登神长阶" };
	do
	{
		choice = choiceOutput("你决定:", choices);
		y += 100;
		switch (choice)
		{
		case 1:
			streamOutput("石门上模糊地刻着一行字:", 10, 1);
			streamOutput("JuFireStudio", 10, 1);
			streamOutput("啊...难道是防伪标识吗...", 10, 1);
			break;
		case 2:
			streamOutput("天空是蔚蓝色, 窗外有千纸鹤...(bushi)", 10, 1);
			break;
		case 3:
			streamOutput("平平无奇的方块儿...", 10, 1);
			streamOutput("你曾经注视过良久.可是它依然是平平无奇的方块儿...", 10, 1);
			streamOutput("......", 60, 1);
			streamOutput("它变了吗...", 10, 1);
			streamOutput("像是历经几十年的风霜, 从任天堂时代走来的方块儿吗...", 10, 1);
			streamOutput("它一直没变, 却好像变了很多.", 10, 1);
			streamOutput("是时代变了吧. 从电子游戏刚刚诞生, 到如今的繁荣盛世.", 10, 1);
			break;
		case 4:
			streamOutput("坑其实不深. 泥土有Minecraft的质感.", 10, 1);
			streamOutput("你的脑海里似乎浮现出黄昏, 木船, 大海...", 10, 1);
			streamOutput("那是你的童年吗...", 10, 1);
			break;
		default:
			break;
		}
	} while (choice != 5);
	clean();

	// 第五关报幕
	streamOutput("是熟悉的阶梯...", 10, 1);
	choices = { "观察通道入口", "观察台阶", "观察手中的方盒", "观察城堡的门", "进入城堡" };
	do
	{
		choice = choiceOutput("你决定:", choices);
		switch (choice)
		{
		case 1:
			streamOutput("JuFireStudio...", 10, 1);
			streamOutput("(爝火工作室)", 10, 1);
			break;
		case 2:
			streamOutput("和当年任天堂同款的像素风方块.", 10, 1);
			streamOutput("就是他把电子游戏从生死的转折点救了回来.", 10, 1);
			break;
		case 3:
			streamOutput("方盒子有点分量, 一部分像是坚硬的金属材质.", 10, 1);
			streamOutput("上面有一些黑色的按键, 排列整齐.", 10, 1);
			break;
		case 4:
			streamOutput("石制的大门.", 10, 1);
			streamOutput("门上挂着金光闪闪的锁. 光芒与手中的钥匙如出一辙.", 10, 1);
			break;
		default:
			break;
		}
	} while (choice != 5);
	clean();

	// BOSS 关卡
	streamOutput("你来到了最后一扇门前...", 10, 1);
BOSS:
	streamOutput("码神对你说:", 10, 1);
	streamOutput("\"智慧的勇士!码神恭候你的到来.\"", 10, 1);
	streamOutput("\"城堡内是最后的试炼.\"", 10, 1);
	streamOutput("\"完成试炼, 你就可以带着码神的祝福回到现实!\"", 10, 1);
	streamOutput("做好准备, 即将前往最后的试炼...", 10, 1);
	directOutput("\n(按任意键开始试炼)\n", -1);

	streamOutput("WASD移动躲避, Q跳过本关, R重新开始.", 10, 1);
	engine->runGamePacman();
	clean();

	// 游戏结束
	streamOutput("就在拿下最后一颗豆子的刹那!", 10, 1);
	streamOutput("你晃了神.", 10, 1);
	streamOutput("你坐在方盒子面前, 看着尚未合成的2048...", 10, 1);
	clean();

	// 最后结局
	streamOutput("(这里我的想法是, 清屏后生成一份最后一步合成2048的残局, 合成2048结束游戏)", 10, -1);

	delete engine;
	return 0;
}
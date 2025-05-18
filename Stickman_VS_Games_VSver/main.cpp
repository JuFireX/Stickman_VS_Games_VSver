#include <iostream>
#include <sstream>
#include <streambuf>
#include <memory>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "engine.h"

using namespace std;

// 复写自定义输出管理器

class CustomStreambuf : public streambuf
{
public:
    CustomStreambuf(streambuf *original, const string &prefix, const string &suffix)
        : original_(original), prefix_(prefix), suffix_(suffix), new_line_(true)
    {
        // 初始状态，认为是新的一行
    }

protected:
    virtual int_type overflow(int_type c) override
    {
        if (c == '\n')
        {
            // 如果是换行符，标记为新的一行
            new_line_ = true;
            // 在换行符之前添加后缀
            if (!suffix_.empty())
            {
                original_->sputn(suffix_.c_str(), suffix_.size());
            }
            return original_->sputc(c);
        }
        else
        {
            if (new_line_)
            {
                // 如果是新的一行，在输出之前添加前缀
                original_->sputn(prefix_.c_str(), prefix_.size());
                new_line_ = false;
            }
            return original_->sputc(c);
        }
    }

private:
    streambuf *original_; // 原始的流缓冲区
    string prefix_;       // 每行前添加的内容
    string suffix_;       // 每行后添加的内容
    bool new_line_;       // 是否新的一行
};

class CustomOutputManager
{
public:
    CustomOutputManager() : original_cout_(cout.rdbuf()), custom_buf_(nullptr) {}

    // 开启自定义缓冲区
    void startCustomOutput(const string &prefix, const string &suffix)
    {
        if (custom_buf_)
        {
            // 如果已经开启了自定义缓冲区，先关闭
            stopCustomOutput();
        }
        // 创建自定义的缓冲区
        custom_buf_ = make_unique<CustomStreambuf>(original_cout_, prefix, suffix);
        // 将标准输出重定向到自定义缓冲区
        cout.rdbuf(custom_buf_.get());
    }

    // 恢复原始缓冲区
    void stopCustomOutput()
    {
        if (custom_buf_)
        {
            // 恢复原始缓冲区
            cout.rdbuf(original_cout_);
            // 释放自定义缓冲区
            custom_buf_.reset();
        }
    }

private:
    streambuf *original_cout_;               // 原始的输出缓冲区
    unique_ptr<CustomStreambuf> custom_buf_; // 自定义的缓冲区
};

// 等待用户输入
void pause(int timeout)
{
    if (timeout == 0)
    {
        system("set /p \"=>>>\" <nul");
        system("pause >nul");
        cout << endl;
    }
    else
    {
        string command = "choice /C:Y /N /D:Y /T:" + to_string(timeout) + " >nul";
        system(command.c_str());
    }
}

// 根据参数字符串模拟流式输出
void streamOutput(const string &output, int speed, int timeout)
{
    for (char c : output)
    {
        cout << c;
        cout.flush(); // 立即刷新输出缓冲区
        Sleep(speed); // 模拟输出延迟
    }
    cout << endl;
    pause(timeout);
}

// 根据参数字符串直接输出
void directOutput(const string &output, int timeout)
{
    cout << output << endl;
    pause(timeout);
}

// 输出选择
int choiceOutput(const string &output, const vector<string> &choices)
{
    streamOutput(output, 10, 1);
    for (int i = 0; i < choices.size(); i++)
        cout << i + 1 << " -> " << choices[i] << endl;
    char choice = _getch();
    return choice - '0';
}

void initGameCli(int count)
{
    //使用utf-8编码
    //SetConsoleOutputCP(65001);
    //SetConsoleCP(65001);
    //system("chcp 65001");
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
    CustomOutputManager outputManager;
    Engine *engine = new Engine();
    int choice = 0;
    initGameCli(count++);

    // 序章报幕

    streamOutput("你是再临, 正在无聊地玩2048...", 50, 1);
    directOutput("(以游玩2048为目标继续行动)", 0);

    // 序章
    streamOutput("WASD移动, Q跳过本关.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGame2048();
    outputManager.stopCustomOutput();
    system("cls");

    // 第一关报幕
    directOutput("\n突然!\n", 1);
    streamOutput("你的屏幕开始闪烁!!! (你要相信它闪了)", 10, 1);
    streamOutput("天崩..地裂...坠落......", 50, 2);
    directOutput("\n啪唧!!!\n", 1);
    streamOutput("你掉在了一处深不见底的平台...(没磕到甲沟炎)", 10, 1);
    streamOutput("环顾四周, 你发现自己来到了推箱子一般的场地.", 10, 1);
    streamOutput("墙壁非常光滑, 看不出一丝出口的痕迹.", 10, 1);
    streamOutput("看来只能尝试完成这古老的游戏了...!", 10, 1);
    directOutput("\n(以完成推箱子为目标继续行动)\n", 0);
    system("cls");

    // 第一关
    streamOutput("WASD移动, Q跳过本关, R重新开始.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGameSokoban();
    outputManager.stopCustomOutput();
    system("cls");

    // 第一关分支
    streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
    streamOutput("当三个箱子放置到正确的位置后,", 10, 1);
    streamOutput("两侧的墙壁都缓缓移开了厚重的石门...", 10, 1);
    temp = 0;
    do
    {
        choice = choiceOutput("你决定:", {"观察左侧石门", "观察右侧石门", "结束观察"});
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
    system("cls");

    // 第二关报幕
    streamOutput("看起来只能前往马里奥平台了..?", 10, 1);
    streamOutput("如果你不打算往坑里跳的话.(你不打算)", 10, 1);
    streamOutput("于是你转身向门外走去......", 10, 1);
    streamOutput("......", 60, 1);
    streamOutput("......", 60, 1);
    streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
    streamOutput("石门在巨响中关闭.", 10, 1);
    system("cls");

    streamOutput("你来到了马里奥的世界...", 10, 1);
    streamOutput("视线尽头是一座城堡. emmm设定上一般城堡都是需要钥匙才能进的...", 10, 1);
    streamOutput("向前走去,不远处的半空漂浮着一个\"幸运方块\"...", 10, 1);
    choice = choiceOutput("你决定:", {"上蹿下跳", "视而不见", "观察方块", "触碰方块"});
    switch (choice)
    {
    case 1:
        streamOutput("你上蹿下跳,", 10, 1);
        streamOutput("你磕到了甲沟炎...", 100, 1);
        streamOutput("再临 卒.", 150, 0);
        system("cls");
        delete engine;
        goto BEGINING;
    case 2:
        streamOutput("鹅, 不愧是你, 毕竟自古CT不抬头.", 10, 1);
        streamOutput("继续前进, 你发现了一个深坑.", 10, 1);
        choice = choiceOutput("你决定:", {"视而不见继续前进", "观察坑的周围"});
        switch (choice)
        {
        case 1:
            streamOutput("不愧是你.", 100, 1);
            streamOutput("你由于走路平视前方掉入了深坑.", 60, 0);
            streamOutput("再临 卒.", 150, 0);
            system("cls");
            delete engine;
            goto BEGINING;
        case 2:
            streamOutput("坑底好像有一个通道?", 10, 1);
            streamOutput("鹅鹅鹅...", 10, 1);
            streamOutput("你显然不太能直接往坑里跳...(会磕到甲沟炎)", 10, 1);
            streamOutput("蒜了, 回去摸幸运方块吧...", 10, 1);
            system("cls");
            break;
        default:
            break;
        }
    case 3:
        streamOutput("平平无奇的方块儿.", 10, 1);
        streamOutput("你盯着方块儿看了许久, 但这还是平平无奇的方块儿.", 10, 1);
        streamOutput("你克制住打开它的冲动.", 10, 1);
        streamOutput(".......", 60, 1);
    case 4:
        streamOutput("你盯着方块儿看了许久, 它们好像变了...", 10, 1);
        streamOutput("方块边儿不再刻迹斑斑，身上的凹陷也平整了许多.", 10, 1);
        streamOutput("从盖儿下微微透出金色的光芒----甜蜜而诱人.", 10, 1);
        streamOutput("有一瞬间, 你甚至觉得方块儿变成了宝箱.", 10, 1);
        streamOutput("这一刻还是来了...", 10, 1);
        streamOutput("你深吸一口气, 伸出手, 敲了敲方块:", 60, 1);
        streamOutput("地上掉落了一个遥控器一样的方盒子.", 10, 1);
        system("cls");
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
    system("cls");

    directOutput("\n(以探索\"方块的秘仪\"为目标继续行动)\n", 0);
    streamOutput("WASD移动, Q跳过本关, R重新开始.", 10, 1);
    outputManager.startCustomOutput(">>>", "<<<");
    engine->runGameTetris();
    outputManager.stopCustomOutput();
    system("cls");

    // 第二关分支
    streamOutput("你成功了!!! ", 10, 1);
    streamOutput("方块落下, 阶梯之外, 皆化作泡影...", 10, 1);
    streamOutput("码神赞赏你的智慧, 治好了你的甲沟炎!(可以跳在台阶上了)", 10, 1);

    choice = choiceOutput("你决定:", {"跳到台阶顶", "跳到半台阶腰", "跳到台阶脚"});
    switch (choice)
    {
    case 1:
        streamOutput("row~~~~~~bomb!", 60, 1);
        streamOutput("你似乎高估了自己的弹跳力, 倒在最后半个台阶上...", 10, 1);
        streamOutput("再临 卒.", 150, 0);
        system("cls");
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
        streamOutput("再临 卒.", 150, 0);
        system("cls");
        delete engine;
        goto BEGINING;
    default:
        break;
    }

    temp = 0;
    do
    {
        choice = choiceOutput("你决定:", {"钻进通道", "前往城堡", "尝试跳回去"});
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
            streamOutput("(底部小字: 开拓者, 本通道已通过星际安全认证, 钻失败者99%都活着回来了)", 10, 1);
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
            }
            else
            {
                streamOutput("放弃吧. 没用的.", 10, 1);
                temp = 1;
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

    // 第三关报幕
    streamOutput("穿过通道, 你置身于漆黑的井底...", 10, 1);
    streamOutput("直觉告诉你, 这里和你初来时遇见的深渊多少沾点亲戚.", 10, 1);
    streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
    streamOutput("身后的通道传来沉闷的巨响.", 10, 1);
    streamOutput("完了, 这下不得不对付这个石墙了.", 10, 1);

    directOutput("\n(以解开最后一扇门为目标继续行动)\n", 0);
    system("cls");

    // 第三关
    streamOutput("WASD移动和旋转方块, Q跳过本关, R重新开始.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGameSnake();
    outputManager.stopCustomOutput();
    system("cls");

    // BOSS 关卡
    streamOutput("你来到了最后一扇门前...", 10, 1);
    streamOutput("门上挂着一张纸条:", 10, 1);
    streamOutput("「通往下一层的钥匙!」", 10, 1);
    streamOutput("「但你必须要先完成本关!」", 10, 1);

    streamOutput("WASD移动和旋转方块, Q跳过本关, R重新开始.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGamePacman();
    outputManager.stopCustomOutput();
    system("cls");

    // 游戏结束
    streamOutput("恭喜你完成所有关卡！", 10, 0);
    streamOutput("你回到了现实世界，看着手中的遥控器，心中充满了成就感...", 10, 0);
    directOutput("\n(按任意键退出游戏)", 0);

    delete engine;
    return 0;
}
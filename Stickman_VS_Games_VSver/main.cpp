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
    // 使用utf-8编码
    // SetConsoleOutputCP(65001);
    // SetConsoleCP(65001);
    // system("chcp 65001");
    // system("title 火柴人VS电子游戏");
    system("mode con cols=120 lines=30");
    system("cls");
    if (count == 1)
        directOutput("哟! 是新鲜的一周目玩家 :P", 1);
    else if (count == 2)
        directOutput("哦吼? hello, again? ", 1);
    else if (count == 4)
        directOutput("蛤? 你在干嘛?? ", 1);
    else
        directOutput("啧啧啧~~", 1);
    pause(1);
}

// 主流程
int main()
{
    int count = 1;
BEGINING:
    CustomOutputManager outputManager;
    Engine *engine = new Engine();
    int choice = 0;
    initGameCli(count++);

    // 序章报幕
    engine->runGameSokoban();
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
    streamOutput("你的屏幕开始闪烁!!!", 10, 1);
    streamOutput("天崩地裂...", 30, 1);
    streamOutput("坠落......", 60, 2);
    directOutput("\n啪唧!!!\n", 1);
    streamOutput("你掉在了一处深不见底的平台...", 10, 1);
    streamOutput("环顾四周, 你发现自己来到了推箱子的场地.", 10, 1);
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
    do
    {
        choice = choiceOutput("你决定:", {"观察左侧石门", "观察右侧石门", "结束观察"});
        switch (choice)
        {
        case 1:
            streamOutput("左侧石门的墙壁开始缓缓移开, 门外是深不见底的深坑.", 10, 1);
            streamOutput("在不远处的半空, 漂浮着金色的钥匙...", 10, 1);
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
    streamOutput("看起来你只能前往马里奥平台了..?", 10, 1);
    streamOutput("如果他不打算往坑里跳的话.", 10, 1);
    streamOutput("于是你转身向门外走去......", 10, 1);
    streamOutput("......", 60, 1);
    streamOutput("......", 60, 1);
    streamOutput("\n轰隆~~~~~~~~~~\n", 100, 2);
    streamOutput("石门在巨响中关闭.", 10, 1);
    system("cls");

    streamOutput("你来到了马里奥的世界...", 10, 1);
    streamOutput("视线尽头是一座城堡. 嗯, 一般设定上城堡需要钥匙才能进...", 10, 1);
    streamOutput("向前走去,不远处的半空漂浮着一个\"幸运方块\"...", 10, 1);
    choice = choiceOutput("你决定:", {"视而不见", "上蹿下跳", "观察方块", "触碰方块"});
SAVE_BOX:
    switch (choice)
    {
    case 1:
        streamOutput("鹅, 不愧是你, 毕竟自古CT不抬头.", 10, 1);
        streamOutput("继续前进, 你发现了一个深坑.", 10, 1);
        choice = choiceOutput("你决定:", {"视而不见, 继续前进", "观察坑的周围"});
        switch (choice)
        {
        case 1:
            streamOutput("不愧是你.", 100, 1);
            streamOutput("Bad End: 你由于平视前方掉入了深坑.", 10, 0);
            system("cls");
            delete engine;
            goto BEGINING;
        case 2:
            streamOutput("坑底好像有一个通道?", 10, 1);
            streamOutput("鹅鹅鹅...", 10, 1);
            streamOutput("你显然不太能直接往坑里跳...", 10, 1);
            streamOutput("蒜了, 回去摸幸运方块吧...", 10, 1);
            system("cls");
            choice = 3;
            goto SAVE_BOX;
            break;
        default:
            break;
        }
    case 2:
        streamOutput("你上蹿下跳,", 10, 1);
        streamOutput("你磕到了甲沟炎...", 100, 1);
        streamOutput("再临 卒.", 150, 0);
        system("cls");
        delete engine;
        goto BEGINING;
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
    streamOutput("游戏规则:", 10, 1);
    streamOutput("WASD移动, Q跳过本关, R重新开始.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGamePacman();
    engine->runGameSnake();
    engine->runGameTetris();
    // 假设第二关的第三个游戏是推箱子
    engine->runGameSokoban();
    outputManager.stopCustomOutput();
    system("cls");

    // 第二关分支
    streamOutput("\n你成功完成了推箱子，发现遥控器方盒子可以打开!", 10, 1);
    streamOutput("遥控器方盒子里面有一张纸条，上面写着谜题...", 10, 1);
    streamOutput("解开谜题才能打开下一扇门...", 10, 1);
    do
    {
        choice = choiceOutput("你决定稍作停留:", {"解开谜题", "观察遥控器", "结束观察"});
        switch (choice)
        {
        case 1:
            streamOutput("你开始解开谜题...", 10, 1);
            streamOutput("经过一番努力，终于解开了谜题，遥控器亮了起来...", 10, 1);
            streamOutput("遥控器发出“咔嚓”的声音，下一扇门缓缓打开...", 10, 1);
            break;

        case 2:
            streamOutput("遥控器看起来非常古老，表面有很多灰尘...", 10, 1);
            streamOutput("你无法从遥控器中得到更多信息...", 10, 1);
            break;

        default:
            break;
        }
    } while (choice != 3);

    // 第三关报幕
    streamOutput("你发现遥控器方盒子打开了一扇通往神秘世界的门...", 10, 1);
    streamOutput("门后是迷雾缭绕的走廊，尽头有一扇明亮的大门...", 10, 1);
    streamOutput("你走了进去，发现这是经典的俄罗斯方块游戏...", 10, 1);
    directOutput("\n(以解开最后一扇门为目标继续行动)\n", 0);
    system("cls");

    // 第三关
    streamOutput("游戏规则:", 10, 1);
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
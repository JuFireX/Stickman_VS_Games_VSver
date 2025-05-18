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

// ��д�Զ������������

class CustomStreambuf : public streambuf
{
public:
    CustomStreambuf(streambuf *original, const string &prefix, const string &suffix)
        : original_(original), prefix_(prefix), suffix_(suffix), new_line_(true)
    {
        // ��ʼ״̬����Ϊ���µ�һ��
    }

protected:
    virtual int_type overflow(int_type c) override
    {
        if (c == '\n')
        {
            // ����ǻ��з������Ϊ�µ�һ��
            new_line_ = true;
            // �ڻ��з�֮ǰ��Ӻ�׺
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
                // ������µ�һ�У������֮ǰ���ǰ׺
                original_->sputn(prefix_.c_str(), prefix_.size());
                new_line_ = false;
            }
            return original_->sputc(c);
        }
    }

private:
    streambuf *original_; // ԭʼ����������
    string prefix_;       // ÿ��ǰ��ӵ�����
    string suffix_;       // ÿ�к���ӵ�����
    bool new_line_;       // �Ƿ��µ�һ��
};

class CustomOutputManager
{
public:
    CustomOutputManager() : original_cout_(cout.rdbuf()), custom_buf_(nullptr) {}

    // �����Զ��建����
    void startCustomOutput(const string &prefix, const string &suffix)
    {
        if (custom_buf_)
        {
            // ����Ѿ��������Զ��建�������ȹر�
            stopCustomOutput();
        }
        // �����Զ���Ļ�����
        custom_buf_ = make_unique<CustomStreambuf>(original_cout_, prefix, suffix);
        // ����׼����ض����Զ��建����
        cout.rdbuf(custom_buf_.get());
    }

    // �ָ�ԭʼ������
    void stopCustomOutput()
    {
        if (custom_buf_)
        {
            // �ָ�ԭʼ������
            cout.rdbuf(original_cout_);
            // �ͷ��Զ��建����
            custom_buf_.reset();
        }
    }

private:
    streambuf *original_cout_;               // ԭʼ�����������
    unique_ptr<CustomStreambuf> custom_buf_; // �Զ���Ļ�����
};

// �ȴ��û�����
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

// ���ݲ����ַ���ģ����ʽ���
void streamOutput(const string &output, int speed, int timeout)
{
    for (char c : output)
    {
        cout << c;
        cout.flush(); // ����ˢ�����������
        Sleep(speed); // ģ������ӳ�
    }
    cout << endl;
    pause(timeout);
}

// ���ݲ����ַ���ֱ�����
void directOutput(const string &output, int timeout)
{
    cout << output << endl;
    pause(timeout);
}

// ���ѡ��
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
    // ʹ��utf-8����
    // SetConsoleOutputCP(65001);
    // SetConsoleCP(65001);
    // system("chcp 65001");
    // system("title �����VS������Ϸ");
    system("mode con cols=120 lines=30");
    system("cls");
    if (count == 1)
        directOutput("Ӵ! �����ʵ�һ��Ŀ��� :P", 1);
    else if (count == 2)
        directOutput("Ŷ��? hello, again? ", 1);
    else if (count == 4)
        directOutput("��? ���ڸ���?? ", 1);
    else
        directOutput("������~~", 1);
    pause(1);
}

// ������
int main()
{
    int count = 1;
BEGINING:
    CustomOutputManager outputManager;
    Engine *engine = new Engine();
    int choice = 0;
    initGameCli(count++);

    // ���±�Ļ
    engine->runGameSokoban();
    streamOutput("��������, �������ĵ���2048...", 50, 1);
    directOutput("(������2048ΪĿ������ж�)", 0);

    // ����
    streamOutput("WASD�ƶ�, Q��������.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGame2048();
    outputManager.stopCustomOutput();
    system("cls");

    // ��һ�ر�Ļ
    directOutput("\nͻȻ!\n", 1);
    streamOutput("�����Ļ��ʼ��˸!!!", 10, 1);
    streamOutput("�������...", 30, 1);
    streamOutput("׹��......", 60, 2);
    directOutput("\nž��!!!\n", 1);
    streamOutput("�������һ������׵�ƽ̨...", 10, 1);
    streamOutput("��������, �㷢���Լ������������ӵĳ���.", 10, 1);
    streamOutput("ǽ�ڷǳ��⻬, ������һ˿���ڵĺۼ�.", 10, 1);
    streamOutput("����ֻ�ܳ����������ϵ���Ϸ��...!", 10, 1);
    directOutput("\n(�����������ΪĿ������ж�)\n", 0);
    system("cls");

    // ��һ��
    streamOutput("WASD�ƶ�, Q��������, R���¿�ʼ.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGameSokoban();
    outputManager.stopCustomOutput();
    system("cls");

    // ��һ�ط�֧
    streamOutput("\n��¡~~~~~~~~~~\n", 100, 2);
    streamOutput("���������ӷ��õ���ȷ��λ�ú�,", 10, 1);
    streamOutput("�����ǽ�ڶ������ƿ��˺��ص�ʯ��...", 10, 1);
    do
    {
        choice = choiceOutput("�����:", {"�۲����ʯ��", "�۲��Ҳ�ʯ��", "�����۲�"});
        switch (choice)
        {
        case 1:
            streamOutput("���ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ����������׵����.", 10, 1);
            streamOutput("�ڲ�Զ���İ��, Ư���Ž�ɫ��Կ��...", 10, 1);
            break;

        case 2:
            streamOutput("�Ҳ�ʯ�ŵ�ǽ�ڿ�ʼ�����ƿ�, ΢����ŷ����ս���...", 10, 1);
            streamOutput("�����������һ����ƽ̨.", 10, 1);
            break;

        default:
            break;
        }
    } while (choice != 3);
    system("cls");

    // �ڶ��ر�Ļ
    streamOutput("��������ֻ��ǰ�������ƽ̨��..?", 10, 1);
    streamOutput("��������������������Ļ�.", 10, 1);
    streamOutput("������ת����������ȥ......", 10, 1);
    streamOutput("......", 60, 1);
    streamOutput("......", 60, 1);
    streamOutput("\n��¡~~~~~~~~~~\n", 100, 2);
    streamOutput("ʯ���ھ����йر�.", 10, 1);
    system("cls");

    streamOutput("������������µ�����...", 10, 1);
    streamOutput("���߾�ͷ��һ���Ǳ�. ��, һ���趨�ϳǱ���ҪԿ�ײ��ܽ�...", 10, 1);
    streamOutput("��ǰ��ȥ,��Զ���İ��Ư����һ��\"���˷���\"...", 10, 1);
    choice = choiceOutput("�����:", {"�Ӷ�����", "�ϴ�����", "�۲췽��", "��������"});
SAVE_BOX:
    switch (choice)
    {
    case 1:
        streamOutput("��, ��������, �Ͼ��Թ�CT��̧ͷ.", 10, 1);
        streamOutput("����ǰ��, �㷢����һ�����.", 10, 1);
        choice = choiceOutput("�����:", {"�Ӷ�����, ����ǰ��", "�۲�ӵ���Χ"});
        switch (choice)
        {
        case 1:
            streamOutput("��������.", 100, 1);
            streamOutput("Bad End: ������ƽ��ǰ�����������.", 10, 0);
            system("cls");
            delete engine;
            goto BEGINING;
        case 2:
            streamOutput("�ӵ׺�����һ��ͨ��?", 10, 1);
            streamOutput("����...", 10, 1);
            streamOutput("����Ȼ��̫��ֱ����������...", 10, 1);
            streamOutput("����, ��ȥ�����˷����...", 10, 1);
            system("cls");
            choice = 3;
            goto SAVE_BOX;
            break;
        default:
            break;
        }
    case 2:
        streamOutput("���ϴ�����,", 10, 1);
        streamOutput("��ĵ��˼׹���...", 100, 1);
        streamOutput("���� ��.", 150, 0);
        system("cls");
        delete engine;
        goto BEGINING;
    case 3:
        streamOutput("ƽƽ����ķ����.", 10, 1);
        streamOutput("�㶢�ŷ�����������, ���⻹��ƽƽ����ķ����.", 10, 1);
        streamOutput("�����ס�����ĳ嶯.", 10, 1);
        streamOutput(".......", 60, 1);
    case 4:
        streamOutput("�㶢�ŷ�����������, ���Ǻ������...", 10, 1);
        streamOutput("����߶����ٿ̼��߰ߣ����ϵİ���Ҳƽ�������.", 10, 1);
        streamOutput("�ӸǶ���΢΢͸����ɫ�Ĺ�â----���۶�����.", 10, 1);
        streamOutput("��һ˲��, ���������÷��������˱���.", 10, 1);
        streamOutput("��һ�̻�������...", 10, 1);
        streamOutput("������һ����, �����, �����÷���:", 60, 1);
        streamOutput("���ϵ�����һ��ң����һ���ķ�����.", 10, 1);
        system("cls");
        break;
    default:
        break;
    }

    // �ڶ���
    streamOutput("��Ϸ����:", 10, 1);
    streamOutput("WASD�ƶ�, Q��������, R���¿�ʼ.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGamePacman();
    engine->runGameSnake();
    engine->runGameTetris();
    // ����ڶ��صĵ�������Ϸ��������
    engine->runGameSokoban();
    outputManager.stopCustomOutput();
    system("cls");

    // �ڶ��ط�֧
    streamOutput("\n��ɹ�����������ӣ�����ң���������ӿ��Դ�!", 10, 1);
    streamOutput("ң����������������һ��ֽ��������д������...", 10, 1);
    streamOutput("�⿪������ܴ���һ����...", 10, 1);
    do
    {
        choice = choiceOutput("���������ͣ��:", {"�⿪����", "�۲�ң����", "�����۲�"});
        switch (choice)
        {
        case 1:
            streamOutput("�㿪ʼ�⿪����...", 10, 1);
            streamOutput("����һ��Ŭ�������ڽ⿪�����⣬ң������������...", 10, 1);
            streamOutput("ң�������������ꡱ����������һ���Ż�����...", 10, 1);
            break;

        case 2:
            streamOutput("ң�����������ǳ����ϣ������кܶ�ҳ�...", 10, 1);
            streamOutput("���޷���ң�����еõ�������Ϣ...", 10, 1);
            break;

        default:
            break;
        }
    } while (choice != 3);

    // �����ر�Ļ
    streamOutput("�㷢��ң���������Ӵ���һ��ͨ�������������...", 10, 1);
    streamOutput("�ź����������Ƶ����ȣ���ͷ��һ�������Ĵ���...", 10, 1);
    streamOutput("�����˽�ȥ���������Ǿ���Ķ���˹������Ϸ...", 10, 1);
    directOutput("\n(�Խ⿪���һ����ΪĿ������ж�)\n", 0);
    system("cls");

    // ������
    streamOutput("��Ϸ����:", 10, 1);
    streamOutput("WASD�ƶ�����ת����, Q��������, R���¿�ʼ.", 10, 1);
    outputManager.startCustomOutput("", "");
    engine->runGamePacman();
    outputManager.stopCustomOutput();
    system("cls");

    // ��Ϸ����
    streamOutput("��ϲ��������йؿ���", 10, 0);
    streamOutput("��ص�����ʵ���磬�������е�ң���������г����˳ɾ͸�...", 10, 0);
    directOutput("\n(��������˳���Ϸ)", 0);

    delete engine;
    return 0;
}
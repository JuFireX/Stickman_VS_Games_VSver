#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

// 定义函数指针类型，与DLL中的游戏函数签名匹配
typedef void (*StartGameFunc)();

bool loadAndPlayGame(const char* dllPath, const char* functionName)
{
    // 动态加载DLL
    HMODULE hDll = LoadLibraryA(dllPath);

    if (hDll == NULL)
    {
        cout << "Fail to load game dll. Error at: " << GetLastError() << endl;
        return false;
    }

    // 获取DLL中的函数地址
    StartGameFunc gameFunction = (StartGameFunc)GetProcAddress(hDll, functionName);

    if (gameFunction == NULL)
    {
        cout << "Fail to find function: " << functionName << ", Error at: " << GetLastError() << endl;
        FreeLibrary(hDll);
        return false;
    }

    // 调用DLL中的函数
    // cout << "正在运行" << gameName << "..." << endl;
    gameFunction();

    // 释放DLL
    FreeLibrary(hDll);
    return true;
}

void play2048()
{
    loadAndPlayGame("..\\levels\\Game_2048\\output\\level.dll", "startGame2048");
}

void playSokoban()
{
    loadAndPlayGame("..\\levels\\Game_Sokoban\\output\\level.dll", "startGameSokoban");
}

void playSnake()
{
    loadAndPlayGame("..\\levels\\Game_Snake\\output\\level.dll", "startGameSnake");
}

void playTetris()
{
    loadAndPlayGame("..\\levels\\Game_Tetris\\output\\level.dll", "startGameTetris");
}

int main()
{
    int gameChoice;
    cout << "Choose a game:\n";
    cout << "1: 2048\n";
    cout << "2: Sokoban\n";
    cout << "3: Snake\n";
    cout << "4: Tetris\n";
    cout << "Enter the ID: ";
    cin >> gameChoice;

    switch (gameChoice)
    {
    case 1:
        play2048();
        break;
    case 2:
        playSokoban();
        break;
    case 3:
        playSnake();
        break;
    case 4:
        playTetris();
        break;
    default:
        cout << "Unknown ID" << endl;
        break;
    }

    return 0;
}
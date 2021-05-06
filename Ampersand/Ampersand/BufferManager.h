#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

// GAME CONSOLE SETTING

// 0, 1�� ���۴� �����÷���, 2�� ���۴� �ε� ȭ�鿡 ���
#define BUFFER_MAX 3

#define UPDATE_CYCLE 32

#define SCREEN_COL 224
#define SCREEN_ROW 124

#define STAGE_COL 224
#define STAGE_ROW 100

#define TITLE "JUST THREE JUMP AT A TIME"

// COLOR DEFINE
#define BLACK 0
#define BLACK_L 8

#define BLUE 1
#define BLUE_L 9

#define GREEN 2
#define GREEN_L 10

#define CYAN 3
#define CYAN_L 11

#define RED 4
#define RED_L 12

#define PINK 5
#define PINK_L 13

#define YELLOW 6
#define YELLOW_L 14

#define WHITE 7
#define WHITE_L 15

// �ܼ�â ��Ʈ ����
void InitConsoleFont(void);

// �ܼ�â ũ�� ����
void InitConsoleSize(void);

// �ܼ�â Ŀ�� ����
void InitConsoleCursor(void);

// 0��, 1�� ��ũ�� ���� �ʱ�ȭ
void InitBuffer(void);

// 2�� �ε� ȭ�� ���� �ʱ�ȭ
void InitLoadingBuffer(void);

// �ε� ȭ�� ���ۿ� ����
void WriteLoadingBuffer(const char * str);

// �ε� ȭ�� ���ۿ� ���ڿ� ���̱�
void ShowLoadingBuffer(const char * str);
void ShowLoadingBuffer(std::string str);

// �ε� ȭ�� ���� �ݱ�
void CloseLoadingBuffer(void);

// ���� ���ۿ� ���ڿ� ���
void WriteCurrentBuffer(const int &x, const int &y, const char * str);
void WriteCurrentBuffer(const int &x, const int &y, const std::string &str);
void WriteCurrentBuffer(const COORD &pos, const char * str);

// 0��, 1�� ���ۿ� ���ڿ� ���
void WriteBothBuffer(const int &x, const int &y, const char * str);
void WriteBothBuffer(const COORD &pos, const char * str);
void WriteBothBuffer(const COORD &pos, const char &c);

void WriteBothBuffer(const int &x, const int &y, const std::string &str);
void WriteBothBuffer(const COORD &pos, const std::string &str);

// 0��, 1�� ���� �ڹٲٱ�
void FlipDoubleBuffer(const DWORD &delayTime);

// ���� �����
void ClearCurrentBuffer(void);
void ClearBothBuffer(void);

// ���� ����
void ReleaseBothBuffer(void);

// ���� �� �ٲٱ�
void SetCurrrentBufferColor(const unsigned short &text, const unsigned short &back);
void SetBothBufferColor(const unsigned short &text, const unsigned short &back);

// ���� Ŀ�� �̵��ϱ�
void CurrentBufferCursorGoToXY(const int &x, const int &y);
void BothBufferCursorGoToXY(const int &x, const int &y);

// �ʱ�ȭ ����
void InitSetting(void);
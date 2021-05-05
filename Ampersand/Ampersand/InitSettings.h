#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

// GAME CONSOLE SETTING
#define BUFFER_MAX 3

#define UPDATE_CYCLE 32

#define SCREEN_COL 224
#define SCREEN_ROW 124

#define STAGE_COL 224
#define STAGE_ROW 100

#define TITLE "JUST THREE JUMP"

// TEXT DATA
#define GROUND '@'
#define GROUND_0 '%'

#define OBSTACLE '#'
#define OBSTACLE_0 '^'

#define COIN '*'

#define START_POINT '&'

// GAME DATA
#define STAGE_LAST 4
#define LIFE 10

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

void InitConsoleFont(void);
void InitConsoleSize(void);
void InitConsoleCursor(void);

void InitBuffer(void);
void InitLoadingBuffer(void);

void ShowLoadingBuffer(void);
void CloseLoadingBuffer(void);

void WriteCurrentBuffer(int x, int y, const char * str);
void WriteCurrentBuffer(int x, int y,std::string str);
void WriteCurrentBuffer(COORD pos, const char * str);

void WriteBothBuffer(int x, int y, const char * str);
void WriteBothBuffer(COORD pos, const char * str);
void WriteBothBuffer(COORD pos, char c);

void WriteBothBuffer(int x, int y, std::string str);
void WriteBothBuffer(COORD pos, std::string str);

void FlipDoubleBuffer(DWORD delayTime);

void ClearCurrentBuffer(void);
void ClearBothBuffer(void);

void ReleaseDoubleBuffer(void);

void SetCurrrentBufferColor(unsigned short text, unsigned short back);
void SetBothBufferColor(unsigned short text, unsigned short back);

void CurrentBufferCursorGoToXY(const int x, const int y);
void BothBufferCursorGoToXY(const int x, const int y);

void InitSetting(void);
#pragma once

#include <string>

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


void CursorGoToXY(const int x, const int y);
void PrintStringAtXY(const int x, const int y, const std::string &str);

void InitMainMenuString(void);

void SetColor(unsigned short text, unsigned short back);

void PrintMainMenu(void);
void InitPrintScreen(void);
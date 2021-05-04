#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#define UPDATE_CYCLE 32

#define SCREEN_COL 224
#define SCREEN_ROW 124

#define STAGE_COL 224
#define STAGE_ROW 100

#define TITLE "JUST THREE JUMP"

#define GROUND '@'

#define OBSTACLE '#'

#define COIN '*'

#define START_POINT '&'

void InitConsoleFont(void);
void InitConsoleSize(void);
void InitConsoleCursor(void);

void InitSetting(void);
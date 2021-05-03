#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

int GetScreenCol(void);
int GetScreenRow(void);

int GetStageCol(void);
int GetStageRow(void);

std::string GetGameTitle(void);

int GetUpdateCycle(void);

void InitConsoleFont(void);
void InitConsoleSize(void);
void InitConsoleCursor(void);

void InitSetting(void);
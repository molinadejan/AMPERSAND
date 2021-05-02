#pragma once

#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

void CursorGoToXY(const int x, const int y);
void PrintStringAtXY(const int x, const int y, const std::string &str);

void InitMainMenuString(void);
void InitStageString(void);

void PrintMainMenu(void);
void PrintStage(void);

void InitPrintScreen(void);
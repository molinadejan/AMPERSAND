#pragma once

#include "CoordData.h"

#include <string>

void InitStage(int &goalCnt, COORD& startPos, std::string fileName);

char GetStageInfo(const int x, const int y);
void SetStageInfo(const int x, const int y, char c);

void UpdatePlayStage(void);
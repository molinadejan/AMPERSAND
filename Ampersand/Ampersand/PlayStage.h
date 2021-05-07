#pragma once

#include "CoordData.h"

#include <string>

// TEXT DATA
#define GROUND '@'
#define GROUND_0 '%'

#define OBSTACLE '#'
#define OBSTACLE_0 '^'

#define COIN '*'

#define START_POINT '&'

// GAME DATA
#define STAGE_LAST 7
#define LIFE 10

// �������� �ʱ�ȭ
void InitStage(int &goalCnt, COORD& startPos, std::string fileName);

// �������� ���� ��ȯ
char GetStageInfo(const int &x, const int &y);

// �������� ����
void SetStageInfo(const int &x, const int &y, const char c);

// ���� ����
void MainLoop(void);
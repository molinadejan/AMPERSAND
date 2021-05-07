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

// 스테이지 초기화
void InitStage(int &goalCnt, COORD& startPos, std::string fileName);

// 스테이지 정보 반환
char GetStageInfo(const int &x, const int &y);

// 스테이지 설정
void SetStageInfo(const int &x, const int &y, const char c);

// 메인 루프
void MainLoop(void);
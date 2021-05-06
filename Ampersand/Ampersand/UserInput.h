#pragma once

#include <Windows.h>
#include <conio.h>

// 플레이어 이동을 위한 좌우 연속 입력 감지
int GetInputLRForPlayer(void);

// 플레이어 점프를 위한 스페이스 불연속 감지
bool GetInputSpace(void);
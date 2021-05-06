#pragma once

#include <Windows.h>

// 해당 위치(월드 좌표)에 게임오버 문자열 출력
void PrintGameover(COORD pos);

// 해당 위치(월드 좌표)에 스테이지 클리어 문자열 출력
void PrintStageClear(COORD pos);
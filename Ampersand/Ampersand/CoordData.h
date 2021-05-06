#pragma once

#include "BufferManager.h"

// 월드 좌표를 스크린 좌표로 변환
COORD WorldToScreen(const SHORT &x, const SHORT &y);
COORD WorldToScreen(const COORD &pos);

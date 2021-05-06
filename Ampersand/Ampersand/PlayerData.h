#pragma once

#include "CoordData.h"

// 플레이어 데이터
typedef struct _playerData
{
	// 현재 위치
	COORD pos;

	// 수직 속도
	double xVelocity;

	// 정밀 계산을 위한 실수형 수직 위치
	double xPosDouble;
	
	// 현재 점프한 회수
	int jumpCnt;

	// 생성자
	_playerData(COORD _pos) : pos(_pos), xVelocity(0), xPosDouble(0), jumpCnt(0) {}
	_playerData() : pos({ 98, 2 }), xVelocity(0), xPosDouble(0), jumpCnt(0) {}

} playerData;
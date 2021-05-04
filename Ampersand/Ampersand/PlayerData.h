#pragma once

#include "CoordData.h"

typedef struct _playerData
{
	COORD pos;

	double xVelocity;
	double xPosDouble;

	int jumpCnt;

	_playerData(COORD _pos) : pos(_pos), xVelocity(0), xPosDouble(0), jumpCnt(0) {}
	_playerData() : pos({ 98, 2 }), xVelocity(0), xPosDouble(0), jumpCnt(0) {}

} playerData;
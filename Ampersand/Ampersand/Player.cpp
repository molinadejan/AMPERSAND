#include "Player.h"

#include "CoordData.h"
#include "Stage.h"
#include "UserInput.h"
#include "BufferManager.h"

// 중력
const double GRAVITY = 500;

// 사이클 ms
const double T = UPDATE_CYCLE / 1000.0;

// T x T / 2
const double TbyTHalf = T * T / 2;

//점프 힘
const double JUMP_POWER = -4000;

void PrintPlayer(const playerData& data, const int &mode)
{
	// mode : 0 -> 플레이어 그리기
	// mode : 1 -> 플레이어 지우기

	COORD screenCoord = WorldToScreen(data.pos);

	if (mode == 0)
		SetBothBufferColor(GREEN_L, GREEN);

	for (int i = 0; i < 5; ++i)
		WriteBothBuffer(screenCoord.X, screenCoord.Y - i, "    ");

	SetBothBufferColor(WHITE, BLACK);
}

void ChangeVerticalPos(playerData& data)
{
	if (data.xVelocity > 0)
	{
		data.xPosDouble += data.xVelocity * TbyTHalf;
		
		for (int i = data.pos.X; i <= (int)data.xPosDouble; ++i)
		{
			if (CheckGround(data, i))
				break;
			else data.pos.X = i;
		}
	}
	else if (data.xVelocity < 0)
	{
		data.xPosDouble += data.xVelocity * TbyTHalf;

		for (int i = data.pos.X; i >= (int)data.xPosDouble; --i)
		{
			if (CheckGround(data, i - 4))
			{
				data.xVelocity = 0;
				break;
			}
			else data.pos.X = i;
		}
	}
	else data.xPosDouble = data.pos.X;
}

void ChangeHorizontalPos(playerData& data, const int &yDir)
{
	int dir;

	if (yDir == -1) dir = -1;
	else if (yDir == 1) dir = 4;
	else return;
	
	for (int i = 0; i < 5; ++i)
	{
		if (GetStageInfo(data.pos.X - i, data.pos.Y + dir) == GROUND)
			return;
	}

	data.pos.Y += yDir;
}

void GetGravity(playerData& data)
{
	if (CheckGround(data, data.pos.X + 1) && data.xVelocity >= 0)
	{
		data.xVelocity = 0;
		data.jumpCnt = 0;
	}
	else data.xVelocity += GRAVITY;
}

bool CheckGround(const playerData& data, const int &xPos)
{
	for (int i = 0; i < 4; ++i)
		if (GetStageInfo(xPos, data.pos.Y + i) == GROUND)
			return true;

	return false;
}

void Jump(playerData& data)
{
	if (data.jumpCnt < 3)
	{
		++data.jumpCnt;
		data.xVelocity = JUMP_POWER;
	}
}

int CheckCollision(const playerData& data)
{
	int ret = 0;

	for (int i = data.pos.X; i > data.pos.X - 5; --i)
	{
		for (int j = data.pos.Y; j < data.pos.Y + 4; ++j)
		{
			if (GetStageInfo(i, j) == OBSTACLE)
				return -1;
			else if (GetStageInfo(i, j) == COIN)
			{
				SetStageInfo(i, j, ' ');
				++ret;
			}
		}
	}

	return ret;
}

void PlayerLoop(playerData& data)
{
	PrintPlayer(data, 1);

	ChangeHorizontalPos(data, GetInputLRForPlayer());
	GetGravity(data);

	if (GetInputSpace())
		Jump(data);

	ChangeVerticalPos(data);

	PrintPlayer(data, 0);
}
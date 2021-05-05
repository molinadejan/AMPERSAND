#include "Player.h"
#include "CoordData.h"
#include "PrintScreen.h"
#include "PlayStage.h"
#include "UserInput.h"

// player row = 5;
// player col = 4;

//const std::string player[2][5] = { {"....", "....","....","_  _","...."}, {"    ", "    ", "    ", "    ", "    "} };
const std::string player[5] = {"    ", "    ","    ","    ","    "};

const double GRAVITY = 500;
const double T = UPDATE_CYCLE / 1000.0;
const double JUMP_POWER = -4000;

void PrintPlayer(playerData& data, int mode)
{
	COORD screenCoord = WorldToScreen(data.pos);

	if(mode == 0)
		SetBothBufferColor(GREEN_L, GREEN);

	for (int i = 0; i < 5; ++i)
		WriteBothBuffer(screenCoord.X, screenCoord.Y - i, player[i]);

	SetBothBufferColor(WHITE, BLACK);
}

void ChangeXPos(playerData& data)
{
	if (data.xVelocity > 0)
	{
		data.xPosDouble += data.xVelocity * T * T / 2;
		
		for (int i = data.pos.X; i <= (int)data.xPosDouble; ++i)
		{
			if (CheckGround(data, i))
				break;
			else data.pos.X = i;
		}
	}
	else if (data.xVelocity < 0)
	{
		data.xPosDouble += data.xVelocity * T * T / 2;

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

void ChangeYPos(playerData& data, int yDir)
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

bool CheckGround(playerData& data, int xPos)
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

int CheckCollision(playerData& data)
{
	int ret = 0;

	for (int i = data.pos.X; i > data.pos.X - 5; --i)
	{
		for (int j = data.pos.Y; j < data.pos.Y + 4; ++j)
		{
			if (GetStageInfo(i, j) == OBSTACLE)
			{
				WriteCurrentBuffer(3, 9, "GAME OVER");
				return - 1;
			}
			else if (GetStageInfo(i, j) == COIN)
			{
				SetStageInfo(i, j, ' ');
				++ret;
			}
		}
	}

	return ret;
}

void UpdatePlayer(playerData& data)
{
	PrintPlayer(data, 1);

	ChangeYPos(data, GetInputLRForPlayer());
	GetGravity(data);

	if (GetInputSpace())
		Jump(data);

	ChangeXPos(data);

	PrintPlayer(data, 0);
}
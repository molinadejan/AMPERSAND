#include "Player.h"
#include "CoordData.h"
#include "PrintScreen.h"
#include "PlayStage.h"
#include "UserInput.h"

const std::string player[2][5] = { {"&&&&","&&&&","&&&&","&&&&","&&&&"}, {"    ", "    ", "    ", "    ", "    "} };

const double gravity = 98 * 2;
const double t = 32 / 1000.0;
const double accel = gravity;
const double jumpPower = -3000;

// World Position
const coord INITPOS = { 30, 2 };

// World Position
coord curPos;

double xVelocity;
double xPosDouble;

// Player is 5 X 4
void InitPlayer(void)
{
	curPos = INITPOS;
	xPosDouble = INITPOS.x;
	xVelocity = 0;
}

void PrintPlayer(int mode)
{
	coord screenCoord = WorldToScreen(curPos);

	for (int i = 0; i < 5; ++i)
		PrintStringAtXY(screenCoord.x, screenCoord.y - i, player[mode][i]);
}

void ChangeXPos(void)
{
	if (xVelocity > 0)
	{
		xPosDouble += xVelocity * t * t / 2;
		
		for (int i = curPos.x; i <= (int)xPosDouble; ++i)
		{
			if (CheckGround(i))
				break;
			else
				curPos.x = i;
		}
	}
	else if (xVelocity < 0)
	{
		xPosDouble += xVelocity * t * t / 2;

		for (int i = curPos.x; i >= (int)xPosDouble; --i)
		{
			if (CheckGround(i - 4))
			{
				xVelocity = 0;
				break;
			}
			else curPos.x = i;
		}
	}
	else
	{
		xPosDouble = curPos.x;
	}
}

void ChangeYPos(int yDir)
{
	int dir;

	if (yDir == -1) dir = -1;
	else if (yDir == 1) dir = 4;
	else return;
	
	for (int i = 0; i < 5; ++i)
	{
		if (GetStageInfo(curPos.x - i, curPos.y + dir) == '@')
			return;
	}

	curPos.y += yDir;
	
	/*curPos.x = curPos.x < 5 ? 5 : curPos.x;
	curPos.x = curPos.x > 98 ? 98 : curPos.x;

	curPos.y = curPos.y < 1 ? 1 : curPos.y;
	curPos.y = curPos.y > 219 ? 219 : curPos.y;*/
}

void GetGravity(void)
{
	if (CheckGround(curPos.x + 1))
		xVelocity = 0;
	else
		xVelocity += accel;
}

bool CheckGround(int xPos)
{
	for (int i = 0; i < 4; ++i)
		if (GetStageInfo(xPos, curPos.y + i) == '@')
			return true;

	return false;
}

void Jump(void)
{
	xVelocity = jumpPower;
}

void UpdatePlayer(void)
{
	//PrintStringAtXY(0, 0, std::to_string(xPosDouble));
	//PrintStringAtXY(0, 1, std::to_string(curPos.x));
	//PrintStringAtXY(0, 1, std::to_string(xVelocity));

	PrintPlayer(1);

	ChangeYPos(GetInputLRForPlayer());
	GetGravity();

	if (GetInputSpace())
		Jump();

	ChangeXPos();

	PrintPlayer(0);
}
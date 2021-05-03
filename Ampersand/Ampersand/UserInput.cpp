#include "UserInput.h"

#define CNT_MAX 1000000000

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,

	MAGICKEY = 224,
	KEYCHECK = 0x8000
};

// Left, Right Arrow Input for control player
int GetInputLRForPlayer(void)
{
	int ret = 0;

	if (GetAsyncKeyState(VK_RIGHT) & KEYCHECK)
		ret = 1;
	else if (GetAsyncKeyState(VK_LEFT) & KEYCHECK)
		ret = -1;

	return ret;
}

int justOneInputForLR = 0;

// Left, Right Arrow Input for UI
int GetInputLRForUI(void)
{
	int ret = 0;

	if (GetAsyncKeyState(VK_RIGHT) & KEYCHECK)
		ret = 1;
	else if (GetAsyncKeyState(VK_LEFT) & KEYCHECK)
		ret = -1;

	if (ret)
	{
		++justOneInputForLR;

		if (justOneInputForLR > CNT_MAX)
			justOneInputForLR = 2;
	}
	else justOneInputForLR = 0;

	if (ret && justOneInputForLR == 1) return ret;

	return 0;
}

int justOneInputForSpace = 0;

// Space Input
bool GetInputSpace(void)
{
	bool check = false;

	if (GetAsyncKeyState(VK_SPACE) & KEYCHECK)
		check = true;

	if (check)
	{
		++justOneInputForSpace;

		if (justOneInputForSpace > CNT_MAX)
			justOneInputForSpace = 2;
	}
	else justOneInputForSpace = 0;

	if (check && justOneInputForSpace == 1) return true;

	return false;
}

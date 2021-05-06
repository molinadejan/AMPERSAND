#include "UserInput.h"

#define CNT_MAX 10

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,

	MAGICKEY = 224,
	KEYCHECK = 0x8000
};

int GetInputLRForPlayer(void)
{
	int ret = 0;

	if (GetAsyncKeyState(VK_RIGHT) & KEYCHECK)
		ret = 1;
	else if (GetAsyncKeyState(VK_LEFT) & KEYCHECK)
		ret = -1;

	return ret;
}

int justOneInputForSpace = 0;

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

	// 스페이스를 계속 누르고 있는 것 방지

	if (check && justOneInputForSpace == 1) return true;

	return false;
}

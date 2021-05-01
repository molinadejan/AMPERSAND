#include "UserInput.h"

enum KEYBOARD
{
	UP = 72,
	DOWN = 80,
	MAGICKEY = 224,
	KEYUP = 0x1
};

// Left, Right Arrow Input
int GetInputLR(void)
{
	int ret = 0;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8001)
		ret = 1;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8001)
		ret = -1;

	return ret;
}

// Up, Down Arrow Input
int GetInputUD(void)
{
	int ret = 0;

	int input = _getch();
	
	if (input == MAGICKEY)
	{
		switch (_getch())
		{
			case UP:
				ret = 1;
				break;

			case DOWN:
				ret = -1;
				break;
		}
	}

	return ret;
}

// Space Input
bool GetInputSpace(void)
{
	bool ret = false;

	if (GetAsyncKeyState(VK_SPACE) & KEYUP)
		ret = true;

	return ret;
}

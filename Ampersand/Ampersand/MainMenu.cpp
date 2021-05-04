#include "MainMenu.h"

enum MENUSTATE
{
	INIT = -1,
	PLAY = 0,
	EXIT = 1,
};

const int arrowMenu0Xpos = 45;
const int arrowMenu1Xpos = 117;

const int arrowYposStart = 107;
const int arrowLineCount = 8;

const std::string arrow[2][4] = { { "##", "###", "####", "#####" }, { "  ", "   ", "    ", "     " } };

void PrintArrow(int menuNum)
{
	for (int i = 0; i < arrowLineCount / 2; ++i)
	{
		PrintStringAtXY(arrowMenu0Xpos, arrowYposStart + i, arrow[menuNum][i]);
		PrintStringAtXY(arrowMenu1Xpos, arrowYposStart + i, arrow[1 - menuNum][i]);
	}

	for (int i = arrowLineCount / 2; i < arrowLineCount; ++i)
	{
		PrintStringAtXY(arrowMenu0Xpos, arrowYposStart + i, arrow[menuNum][arrowLineCount - i - 1]);
		PrintStringAtXY(arrowMenu1Xpos, arrowYposStart + i, arrow[1 - menuNum][arrowLineCount - i - 1]);
	}
}

void MoveMenu(int &currentMenu)
{
	++currentMenu;
	currentMenu %= 2;

	PrintArrow(currentMenu);
}

void UpdateMainMenu()
{
	PrintMainMenu();
	int currentMenu = INIT;

	while (true)
	{
		if (GetInputLRForUI())
		{
			MoveMenu(currentMenu);
		}

		if (GetInputSpace())
		{
			if (currentMenu == PLAY)
				;
			else if (currentMenu == EXIT)
				exit(0);
		}

		Sleep(UPDATE_CYCLE);
	}
}

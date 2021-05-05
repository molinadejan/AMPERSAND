#include "PrintScreen.h"

#include "InitSettings.h"
#include "CoordData.h"

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

std::string mainMenuString = "";

void InitMainMenuString(void)
{
	std::string inLine;
	std::ifstream in("MainMenu.txt");

	while (std::getline(in, inLine))
	{
		mainMenuString.append(inLine).append("\n");
		mainMenuString.append(inLine).append("\n");
	}

	in.close();
}

void PrintMainMenu(void)
{
	//std::cout << mainMenuString;
}

void PrintGameover(COORD pos)
{
	COORD _pos = WorldToScreen(pos);

	WriteBothBuffer(_pos.X + 4, _pos.Y - 4, "       ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 3, " oops! ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 2, "       ");
}

void InitPrintScreen(void)
{
	InitMainMenuString();
}
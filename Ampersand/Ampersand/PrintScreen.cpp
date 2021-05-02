#include "PrintScreen.h"

std::string mainMenuString = "";
std::string stageString = "";

// console cursor move to X, Y
void CursorGoToXY(const int x, const int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}

void PrintStringAtXY(const int x, const int y, const std::string &str)
{
	CursorGoToXY(x, y);
	std::cout << str;
}

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

void InitStageString(void)
{
	std::string inLine;
	std::ifstream in("Stage.txt");

	while (std::getline(in, inLine))
		stageString.append(inLine).append("\n");

	in.close();
}

void PrintMainMenu(void)
{
	std::cout << mainMenuString;
}

void PrintStage(void)
{
	CursorGoToXY(0, 12);
	std::cout << stageString;
}

void InitPrintScreen(void)
{
	InitMainMenuString();
	InitStageString();
}
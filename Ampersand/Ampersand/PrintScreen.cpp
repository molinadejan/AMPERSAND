#include "PrintScreen.h"

// console cursor move to X, Y
void CursorGoToXY(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}

void PrintMainMenu()
{
	std::string inLine;
	std::ifstream in("MainMenu.txt");

	while (std::getline(in, inLine))
	{
		std::cout << inLine << "\n";
		std::cout << inLine << "\n";
	}

	in.close();
}
// Code for VS2017

#include "InitSettings.h"
#include "UserInput.h"
#include "PrintScreen.h"

using namespace std;

int main(void)
{
	InitConsoleFont();
	InitConsoleSize();
	InitConsoleCursor();

	PrintMainMenu();

	/*while (true)
	{
		Sleep(32);
	}*/

	return 0;
}
#include "InitSettings.h"

// Change console font to Raster
// Font size is 8 X 8
void InitConsoleFont(void)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;
	cfi.FontFamily = FF_DONTCARE;
	//cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

// Change console window size 200 * 100
void InitConsoleSize(void)
{
	SetWindowPos(GetConsoleWindow(), 0, 0, 0, 0, 0, SWP_NOZORDER);

	std::string command = "mode con:cols=" + std::to_string(SCREEN_COL) + " lines=" + std::to_string(SCREEN_ROW) + " | title " + TITLE;
	system(command.c_str());
}

// Hide console cursor
void InitConsoleCursor(void)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO consoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &consoleCursor);
}

void InitSetting(void)
{
	InitConsoleFont();
	InitConsoleSize();
	InitConsoleCursor();
}
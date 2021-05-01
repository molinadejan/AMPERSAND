#include "InitSettings.h"

// Entire Console Size : 225 * 125

// Game Play Screen Size : 200 * 100
// 나중에 좌표 변환 코드 작성 필요!!!!

const int SCREEN_COL = 225;
const int SCREEN_ROW = 125;
const std::string GAME_TITLE = "I AM APERSAND";

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

	std::string command = "mode con:cols=" + std::to_string(SCREEN_COL) + " lines=" + std::to_string(SCREEN_ROW) + " | title " + GAME_TITLE;
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
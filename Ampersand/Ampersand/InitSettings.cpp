#include "InitSettings.h"

// Entire Console Size : 224 * 124
// Game Play Screen Size : 224 * 100
// 나중에 좌표 변환 코드 작성 필요!!!!

//const int SCREEN_COL = 224;
int GetScreenCol(void) { return 224; }

//const int SCREEN_ROW = 124;
int GetScreenRow(void) { return 124; }

//const int STAGE_COL = 224;
int GetStageCol(void) { return 224; }

//const int STAGE_ROW = 100;
int GetStageRow(void) { return 100; }

//const std::string GAME_TITLE = "I AM AMPERSAND";
std::string GetGameTitle(void) { return "I AM AMPERSAND"; }

//const int UPDATE_CYCLE = 32;
int GetUpdateCycle(void) { return 32; }

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

	std::string command = "mode con:cols=" + std::to_string(GetScreenCol()) + " lines=" + std::to_string(GetScreenRow()) + " | title " + GetGameTitle();
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
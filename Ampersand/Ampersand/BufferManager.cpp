#include "BufferManager.h"

#include <Windows.h>
#include <string>

static int nBufferIndex;

static HANDLE hBuffer[BUFFER_MAX];

void InitConsoleFont(void)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void InitConsoleSize(void)
{
	SetWindowPos(GetConsoleWindow(), 0, 0, 0, 0, 0, SWP_NOZORDER);

	std::string command = "mode con:cols=" + std::to_string(SCREEN_COL) + " lines=" + std::to_string(SCREEN_ROW) + " | title " + TITLE;
	system(command.c_str());
}

void InitConsoleCursor(void)
{
	CONSOLE_CURSOR_INFO consoleCursor;

	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hBuffer[0], &consoleCursor);
	SetConsoleCursorInfo(hBuffer[1], &consoleCursor);
	SetConsoleCursorInfo(hBuffer[2], &consoleCursor);
}

void InitBuffer(void)
{
	SMALL_RECT rect = { 0, 0, SCREEN_COL - 1, SCREEN_ROW - 1};

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleWindowInfo(hBuffer[0], true, &rect);
	SetConsoleWindowInfo(hBuffer[1], true, &rect);

	SetConsoleScreenBufferSize(hBuffer[0], { SCREEN_COL, SCREEN_ROW });
	SetConsoleScreenBufferSize(hBuffer[1], { SCREEN_COL, SCREEN_ROW });

	InitConsoleCursor();
}

void InitLoadingBuffer(void)
{
	SMALL_RECT rect = { 0, 0, SCREEN_COL - 1, SCREEN_ROW - 1 };

	hBuffer[2] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleWindowInfo(hBuffer[2], true, &rect);
	SetConsoleScreenBufferSize(hBuffer[2], { SCREEN_COL, SCREEN_ROW });

	InitConsoleCursor();
}

void WriteLoadingBuffer(const char * str)
{
	DWORD dw;
	COORD CursorPosition = { 110, 62 };
	SetConsoleCursorPosition(hBuffer[2], CursorPosition);

	WriteFile(hBuffer[2], str, strlen(str), &dw, NULL);
}

void ShowLoadingBuffer(const char * str)
{
	WriteLoadingBuffer("                              ");
	WriteLoadingBuffer(str);
	SetConsoleActiveScreenBuffer(hBuffer[2]);
}

void ShowLoadingBuffer(std::string str)
{
	ShowLoadingBuffer(str.c_str());
}

void CloseLoadingBuffer(void)
{
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
}

void WriteCurrentBuffer(const int &x, const int &y, const char * str)
{
	DWORD dw;
	COORD CursorPosition = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(hBuffer[nBufferIndex], CursorPosition);
	WriteFile(hBuffer[nBufferIndex], str, strlen(str), &dw, NULL);
}

void WriteCurrentBuffer(const int &x, const int &y, const std::string &str)
{
	WriteCurrentBuffer(x, y, str.c_str());
}

void WriteCurrentBuffer(const COORD &pos, const char * str)
{
	DWORD dw;
	SetConsoleCursorPosition(hBuffer[nBufferIndex], pos);
	WriteFile(hBuffer[nBufferIndex], str, strlen(str), &dw, NULL);
}


void WriteBothBuffer(const int &x, const int &y, const char * str)
{
	DWORD dw;
	COORD CursorPosition = { SHORT(x), SHORT(y) };

	SetConsoleCursorPosition(hBuffer[0], CursorPosition);
	WriteFile(hBuffer[0], str, strlen(str), &dw, NULL);

	SetConsoleCursorPosition(hBuffer[1], CursorPosition);
	WriteFile(hBuffer[1], str, strlen(str), &dw, NULL);
}

void WriteBothBuffer(const COORD &pos, const char * str)
{
	DWORD dw;

	SetConsoleCursorPosition(hBuffer[0], pos);
	WriteFile(hBuffer[0], str, strlen(str), &dw, NULL);

	SetConsoleCursorPosition(hBuffer[1], pos);
	WriteFile(hBuffer[1], str, strlen(str), &dw, NULL);
}

void WriteBothBuffer(const COORD &pos, const char &c)
{
	char str[2] = { c, 0 };
	WriteBothBuffer(pos, str);
}

void WriteBothBuffer(const int &x, const int &y, const std::string &str)
{
	WriteBothBuffer(x, y, str.c_str());
}

void WriteBothBuffer(const COORD &pos, const std::string &str)
{
	WriteBothBuffer(pos, str.c_str());
}


void FlipDoubleBuffer(const DWORD &delayTime)
{
	Sleep(delayTime);
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
	nBufferIndex = !nBufferIndex;
}

void ClearCurrentBuffer(void)
{
	COORD coord = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nBufferIndex], ' ', SCREEN_COL * SCREEN_ROW, coord, &dw);
}

void ClearBothBuffer(void)
{
	COORD coord = { 0,0 };
	DWORD dw;

	FillConsoleOutputCharacter(hBuffer[0], ' ', SCREEN_COL * SCREEN_ROW, coord, &dw);
	FillConsoleOutputCharacter(hBuffer[1], ' ', SCREEN_COL * SCREEN_ROW, coord, &dw);
}

void ReleaseBothBuffer(void)
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

void SetCurrrentBufferColor(const unsigned short &text, const unsigned short &back)
{
	SetConsoleTextAttribute(hBuffer[nBufferIndex], text | (back << 4));
}

void SetBothBufferColor(const unsigned short &text, const unsigned short &back)
{
	SetConsoleTextAttribute(hBuffer[0], text | (back << 4));
	SetConsoleTextAttribute(hBuffer[1], text | (back << 4));
}

void CurrentBufferCursorGoToXY(const int &x, const int &y)
{
	SetConsoleCursorPosition(hBuffer[nBufferIndex], { (SHORT)x, (SHORT)y });
}

void BothBufferCursorGoToXY(const int &x, const int &y)
{
	SetConsoleCursorPosition(hBuffer[0], { (SHORT)x, (SHORT)y });
	SetConsoleCursorPosition(hBuffer[1], { (SHORT)x, (SHORT)y });
}

void InitSetting(void)
{
	InitConsoleFont();
	InitConsoleSize();
	InitLoadingBuffer();
}
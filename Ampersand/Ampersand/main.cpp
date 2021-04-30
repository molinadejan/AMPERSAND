﻿// Code for VS2017

#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int InputRL()
{
	int ret = 0;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8001)
		ret = 1;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8001)
		ret = -1;

	return ret;
}

int InputUD()
{
	int ret = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001)
		ret = -1;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
		ret = 1;

	return ret;
}

int main(void)
{
	int posX = 10, posY = 10, prevX = 10, prevY = 10;

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;
	cfi.FontFamily = FF_DONTCARE;
	//cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	system("mode con:cols=200 lines=100");

	while (true)
	{
		//system("cls");

		int hor = InputRL();
		int ver = InputUD();

		if (hor != 0 || ver != 0)
		{
			gotoxy(posX, posY);
			cout << ' ';

			posX += hor;
			posY += ver;

			posX = posX < 0 ? 0 : posX;
			posX = posX >= 200 ? 199 : posX;
			posY = posY < 0 ? 0 : posY;
			posY = posY >= 100 ? 99 : posY;
		}

		gotoxy(posX, posY);
		cout << '&';

		Sleep(32);
	}

	return 0;
}
// Code for VS2017

#include "InitSettings.h"
#include "UserInput.h"
#include "PrintScreen.h"
#include "MainMenu.h"

using namespace std;

int main(void)
{
	// 콘솔창 초기 세팅
	InitSetting();

	// 각종 화면 데이터로 저장
	InitPrintScreen();

	PrintStage();

	while (true)
	{
		Sleep(32);
	}

	return 0;
}
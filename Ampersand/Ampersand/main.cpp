// Code for VS2017

#include "InitSettings.h"
#include "PrintScreen.h"
#include "MainMenu.h"
#include "PlayStage.h"

using namespace std;

int main(void)
{
	// 콘솔창 초기 세팅
	InitSetting();

	// 각종 화면 데이터로 저장
	InitPrintScreen();

	UpdatePlayStage();

	return 0;
}
#include "PlayStage.h"
#include "InitSettings.h"
#include "Player.h"
#include "PrintScreen.h"

std::string stage[100];

void InitStage(void)
{
	std::string inLine;
	std::ifstream in("Stage.txt");

	int lineCnt = 0;
	CursorGoToXY(0, 12);

	while (std::getline(in, inLine))
	{
		stage[lineCnt++] = inLine;
		std::cout << inLine << "\n";
	}

	in.close();
}

char GetStageInfo(const int x, const int y)
{
	if (x < 0 || y < 0 || x > 99 || y > 223)
		return '@';

	return stage[x][y];
}

void UpdatePlayStage(void)
{
	InitStage();
	InitPlayer();

	while (true)
	{
		UpdatePlayer();

		Sleep(GetUpdateCycle());
	}
}
#include "PlayStage.h"

#include "InitSettings.h"
#include "Player.h"
#include "PrintScreen.h"
#include "PlayerData.h"

#include <cstdlib>
#include <fstream>

std::string stage[100];

void InitStage(int &goalCnt, COORD& startPos, std::string fileName)
{
	std::string inLine;
	std::ifstream in(fileName);

	int lineCnt = 0;
	goalCnt = 0;
	CursorGoToXY(0, 12);

	while (std::getline(in, inLine))
	{
		stage[lineCnt++] = inLine;

		for (int i = 0; i < STAGE_COL; ++i)
		{
			char c = inLine[i];

			if (c == OBSTACLE)
			{
				int ran = rand() % 2;

				SetColor(ran ? RED : RED_L, BLACK);
				std::cout << (ran ? OBSTACLE : '^');
			}
			else if (c == COIN)
			{
				SetColor(YELLOW, YELLOW_L);
				++goalCnt;

				std::cout << c;
			}
			else if (c == GROUND)
			{
				if(lineCnt == 1 || lineCnt == STAGE_ROW || i == 0 || i == STAGE_COL - 1)
					SetColor(WHITE, rand() % 2 ? WHITE : WHITE_L);
				else
					SetColor(BLUE_L, rand() % 2 ? BLUE : BLUE_L);

				std::cout << (rand() % 2 ? GROUND : '%');
			}
			else if (c == START_POINT)
			{
				startPos = {SHORT(lineCnt - 1), SHORT(i)};
				stage[lineCnt - 1][i] = ' ';
				std::cout << ' ';
			}
			else
			{
				SetColor(WHITE, BLACK);
				std::cout << c;
			}
		}

		std::cout << "\n";
	}

	in.close();

	SetColor(WHITE, BLACK);
}

char GetStageInfo(const int x, const int y)
{
	if (x < 0 || y < 0 || x >= STAGE_ROW || y >= STAGE_COL)
		return GROUND;

	return stage[x][y];
}

void SetStageInfo(const int x, const int y, char c)
{
	if (x < 0 || y < 0 || x >= STAGE_ROW || y >= STAGE_COL)
		return;

	stage[x][y] = c;
}

void UpdatePlayStage(void)
{
	int life = 3, stageCnt = 1;

	while (true)
	{
		int goalCount = 0, collisionCode, currentCoin = 0;
		COORD initPos;

		InitStage(goalCount, initPos, "Stage"+ std::to_string(stageCnt) +".txt");

		playerData data(initPos);

		PrintStringAtXY(3, 3, "Life : " + std::to_string(life));
		PrintStringAtXY(3, 5, "Total Coin : " + std::to_string(goalCount));

		while (true)
		{
			collisionCode = CheckCollision(data);

			if (collisionCode == -1) // 장애물과 충돌
			{
				--life;

				break;
			}
			else currentCoin += collisionCode;

			PrintStringAtXY(3, 7, "Current Coin :" + std::to_string(currentCoin));

			if (currentCoin == goalCount)
			{
				++stageCnt;

				break;
			}

			UpdatePlayer(data);

			Sleep(UPDATE_CYCLE);
		}

		if (life == 0 || stageCnt == 4) break;
	}
}
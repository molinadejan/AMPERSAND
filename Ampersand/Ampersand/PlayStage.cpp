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

	int lineCnt = 0, ran;
	char c;
	goalCnt = 0;

	while (std::getline(in, inLine))
	{
		stage[lineCnt] = inLine;

		for (int i = 0; i < STAGE_COL; ++i)
		{
			c = inLine[i];

			if (c == OBSTACLE)
			{
				ran = rand() % 2;
				SetBothBufferColor(ran ? RED : RED_L, BLACK);

				c = ran ? OBSTACLE : OBSTACLE_0;
			}
			else if (c == COIN)
			{
				SetBothBufferColor(YELLOW, YELLOW_L);
				++goalCnt;
			}
			else if (c == GROUND)
			{
				ran = rand() % 2;

				if(lineCnt == 0 || lineCnt == STAGE_ROW - 1 || i == 0 || i == STAGE_COL - 1)
					SetBothBufferColor(WHITE, WHITE);
				else
					SetBothBufferColor(BLUE_L, rand() % 2 ? BLUE : BLUE_L);

				c = ran ? GROUND : GROUND_0;
			}
			else if (c == START_POINT)
			{
				startPos = {SHORT(lineCnt), SHORT(i)};
				stage[lineCnt][i] = ' ';
			}
			else SetBothBufferColor(WHITE, BLACK);

			WriteBothBuffer(WorldToScreen(lineCnt, i), c);
		}

		++lineCnt;
	}

	in.close();

	SetBothBufferColor(WHITE, BLACK);
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
	int life = LIFE, stageCnt = 4;

	while (true)
	{
		ShowLoadingBuffer();

		int goalCnt = 0, collisionCode, currentCoin = 0;
		COORD initPos;

		ClearBothBuffer();
		InitStage(goalCnt, initPos, "Stage" + std::to_string(stageCnt) + ".txt");

		playerData data(initPos);

		WriteBothBuffer(3, 3, "Life : " + std::to_string(life));
		WriteBothBuffer(3, 5, "Total Coin : " + std::to_string(goalCnt));

		CloseLoadingBuffer();

		while (true)
		{
			collisionCode = CheckCollision(data);

			if (collisionCode == -1) // 장애물과 충돌
			{
				--life;

				PrintGameover(data.pos);
				Sleep(2000);

				break;
			}
			else currentCoin += collisionCode;

			WriteCurrentBuffer(3, 7, "Current Coin :" + std::to_string(currentCoin));

			if (currentCoin == goalCnt)
			{
				++stageCnt;

				break;
			}

			UpdatePlayer(data);

			FlipDoubleBuffer(UPDATE_CYCLE);
		}

		if (life == 0 || stageCnt > STAGE_LAST)
			break;
	}
}
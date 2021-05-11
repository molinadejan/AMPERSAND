#include "Stage.h"

#include "BufferManager.h"
#include "Player.h"
#include "PrintScreen.h"
#include "PlayerData.h"
\
#include <fstream>

// 스테이지 문자열로 저장
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
					SetBothBufferColor(WHITE, ran ? WHITE : WHITE_L);
				else
					SetBothBufferColor(BLUE_L, rand() % 2 ? BLUE : BLUE_L);

				c = ran ? GROUND : GROUND_0;
			}
			else if (c == START_POINT)
			{
				startPos = {SHORT(lineCnt), SHORT(i)};
				stage[lineCnt][i] = ' ';
			}
			else if (c == ' ') continue;

			WriteBothBuffer(WorldToScreen(lineCnt, i), c);

			SetBothBufferColor(WHITE, BLACK);
		}

		++lineCnt;
	}

	in.close();

	SetBothBufferColor(WHITE, BLACK);
}

char GetStageInfo(const int &x, const int &y)
{
	if (x < 0 || y < 0 || x >= STAGE_ROW || y >= STAGE_COL)
		return GROUND;

	return stage[x][y];
}

void SetStageInfo(const int &x, const int &y, const char c)
{
	if (x < 0 || y < 0 || x >= STAGE_ROW || y >= STAGE_COL)
		return;

	stage[x][y] = c;
}

void GameFinish(int * const stage, int * const life)
{
	if (*stage > STAGE_LAST)
	{
		ShowGameClear();

		*stage = 0;
		*life = LIFE;

		Sleep(6000);
	}
	else if (*life == 0)
	{
		ShowGameover();

		*stage = 0;
		*life = LIFE;

		Sleep(6000);
	}
}

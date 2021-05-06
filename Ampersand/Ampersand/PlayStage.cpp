#include "PlayStage.h"

#include "BufferManager.h"
#include "Player.h"
#include "PrintScreen.h"
#include "PlayerData.h"
\
#include <fstream>

// 스테이지 문자열로 저장
static std::string stage[100];

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

void MainLoop(void)
{
	int life = LIFE, stageCnt = 0;

	while (true)
	{
		// 버퍼 해제, 할당
		ReleaseBothBuffer();
		InitBuffer();

		// 로딩창에 스테이지 단계 출력
		if (stageCnt == 0)
			ShowLoadingBuffer("Now Loading...");
		else if(stageCnt == STAGE_LAST)
			ShowLoadingBuffer("FINAL STAGE");
		else
			ShowLoadingBuffer("STAGE " + std::to_string(stageCnt));

		// 목표 동전 카운트, 충돌 카운트, 현재 모은 동전
		int goalCnt = 0, colCnt, currentCoin = 0;
		
		// 초기위치
		COORD initPos;

		// 버퍼 0으로 초기화
		ClearBothBuffer();

		// 스테이지 초기화
		InitStage(goalCnt, initPos, "Stage" + std::to_string(stageCnt) + ".txt");

		// 플레이어 데이터 생성
		playerData data(initPos);

		// 좌상단 플레이 정보 출력
		if (stageCnt)
		{
			WriteBothBuffer(3, 3, "Life : " + std::to_string(life));
			WriteBothBuffer(3, 5, "Stage " + std::to_string(stageCnt));
			WriteBothBuffer(3, 7, "Total Coin : " + std::to_string(goalCnt));
		}

		Sleep(1000);

		// 로딩 화면 버퍼 숨기기
		CloseLoadingBuffer();

		// 게임 루프
		while (true)
		{
			// 장애물과 충돌했다면 다시
			if ((colCnt = CheckCollision(data)) == -1)
			{
				--life;

				PrintGameover(data.pos);
				Sleep(2000);

				break;
			}
			
			// 코인 추가
			currentCoin += colCnt;

			// 좌상단에 정보 출력
			if(stageCnt)
				WriteCurrentBuffer(3, 9, "Current Coin :" + std::to_string(currentCoin));

			// 모든 코인을 다 모았다면 다음 스테이지로
			if (currentCoin == goalCnt)
			{
				++stageCnt;

				PrintStageClear(data.pos);
				Sleep(2000);

				break;
			}

			// 플레이어 처리
			PlayerLoop(data);

			// 버퍼 바꾸기
			FlipDoubleBuffer(UPDATE_CYCLE);
		}

		// 더이상 남은 라이프가 없으면 게임 오버
		if (life == 0)
		{
			ShowLoadingBuffer("Game Over...");

			stageCnt = 0;
			life = LIFE;

			Sleep(5000);
		}
		// 마지막 스테이지 까지 클리어
		else if (stageCnt > STAGE_LAST)
		{
			ShowLoadingBuffer("Game Clear!!!");

			stageCnt = 0;
			life = LIFE;

			Sleep(5000);
		}
	}
}
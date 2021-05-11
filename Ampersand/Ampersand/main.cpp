#include "BufferManager.h"
#include "Stage.h"
#include "PlayerData.h"
#include "PrintScreen.h"
#include "Player.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <Windows.h>

int main(void)
{
	// 콘솔창 초기 세팅
	InitSetting();

	// 메인 루프 

	int life = LIFE, stage = 0;

	while (true)
	{
		InitBuffer();        // 버퍼 할당
		ClearBothBuffer();   // 버퍼 초기화

		ShowStageLoading(stage); // 로딩창

		int goalCnt = 0;     // 모아야 하는 동전 카운트
		int colCnt = 0;      // 충돌 카운트
		int currentCoin = 0; // 현재 모은 동전
		COORD initPos;       // 플레이어 초기 위치

		InitStage(goalCnt, initPos, "Stage" + std::to_string(stage) + ".txt"); // 스테이지 초기화

		// 플레이어 데이터 생성
		playerData data(initPos);

		// 좌상단 플레이 정보 출력
		if (stage)
		{
			WriteBothBuffer(3, 3, "Life : " + std::to_string(life));
			WriteBothBuffer(3, 5, "Stage " + std::to_string(stage));
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
				PlaySound(TEXT("Die.wav"), 0, SND_FILENAME | SND_ASYNC);

				Sleep(2000);

				break;
			}

			// 코인 추가
			if (colCnt > 0)
			{
				currentCoin += colCnt;

				if (currentCoin != goalCnt)
					PlaySound(TEXT("Coin.wav"), 0, SND_FILENAME | SND_ASYNC);
			}

			// 좌상단에 정보 출력
			if (stage)
				WriteCurrentBuffer(3, 9, "Current Coin :" + std::to_string(currentCoin));

			// 모든 코인을 다 모았다면 다음 스테이지로
			if (currentCoin == goalCnt)
			{
				++stage;

				PlaySound(TEXT("MUYAHO.wav"), 0, SND_FILENAME | SND_ASYNC);

				PrintStageClear(data.pos);
				Sleep(2000);

				break;
			}

			// 플레이어 처리
			PlayerLoop(data);

			// 버퍼 바꾸기
			FlipDoubleBuffer(UPDATE_CYCLE);
		}

		GameFinish(&stage, &life); // 게임 끝 처리
		ReleaseBothBuffer();       // 버퍼 해제
	}

	return 0;
}
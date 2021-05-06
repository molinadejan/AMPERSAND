#include "PlayStage.h"

#include "BufferManager.h"
#include "Player.h"
#include "PrintScreen.h"
#include "PlayerData.h"
\
#include <fstream>

// �������� ���ڿ��� ����
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
		// ���� ����, �Ҵ�
		ReleaseBothBuffer();
		InitBuffer();

		// �ε�â�� �������� �ܰ� ���
		if (stageCnt == 0)
			ShowLoadingBuffer("Now Loading...");
		else if(stageCnt == STAGE_LAST)
			ShowLoadingBuffer("FINAL STAGE");
		else
			ShowLoadingBuffer("STAGE " + std::to_string(stageCnt));

		// ��ǥ ���� ī��Ʈ, �浹 ī��Ʈ, ���� ���� ����
		int goalCnt = 0, colCnt, currentCoin = 0;
		
		// �ʱ���ġ
		COORD initPos;

		// ���� 0���� �ʱ�ȭ
		ClearBothBuffer();

		// �������� �ʱ�ȭ
		InitStage(goalCnt, initPos, "Stage" + std::to_string(stageCnt) + ".txt");

		// �÷��̾� ������ ����
		playerData data(initPos);

		// �»�� �÷��� ���� ���
		if (stageCnt)
		{
			WriteBothBuffer(3, 3, "Life : " + std::to_string(life));
			WriteBothBuffer(3, 5, "Stage " + std::to_string(stageCnt));
			WriteBothBuffer(3, 7, "Total Coin : " + std::to_string(goalCnt));
		}

		Sleep(1000);

		// �ε� ȭ�� ���� �����
		CloseLoadingBuffer();

		// ���� ����
		while (true)
		{
			// ��ֹ��� �浹�ߴٸ� �ٽ�
			if ((colCnt = CheckCollision(data)) == -1)
			{
				--life;

				PrintGameover(data.pos);
				Sleep(2000);

				break;
			}
			
			// ���� �߰�
			currentCoin += colCnt;

			// �»�ܿ� ���� ���
			if(stageCnt)
				WriteCurrentBuffer(3, 9, "Current Coin :" + std::to_string(currentCoin));

			// ��� ������ �� ��Ҵٸ� ���� ����������
			if (currentCoin == goalCnt)
			{
				++stageCnt;

				PrintStageClear(data.pos);
				Sleep(2000);

				break;
			}

			// �÷��̾� ó��
			PlayerLoop(data);

			// ���� �ٲٱ�
			FlipDoubleBuffer(UPDATE_CYCLE);
		}

		// ���̻� ���� �������� ������ ���� ����
		if (life == 0)
		{
			ShowLoadingBuffer("Game Over...");

			stageCnt = 0;
			life = LIFE;

			Sleep(5000);
		}
		// ������ �������� ���� Ŭ����
		else if (stageCnt > STAGE_LAST)
		{
			ShowLoadingBuffer("Game Clear!!!");

			stageCnt = 0;
			life = LIFE;

			Sleep(5000);
		}
	}
}
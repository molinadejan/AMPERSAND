#include "PrintScreen.h"
#include "Stage.h"
#include "BufferManager.h"
#include "CoordData.h"

#include <Windows.h>

void PrintGameover(COORD pos)
{
	COORD _pos = WorldToScreen(pos);

	WriteBothBuffer(_pos.X + 4, _pos.Y - 4, "       ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 3, " oops! ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 2, "       ");
}

void PrintStageClear(COORD pos)
{
	COORD _pos = WorldToScreen(pos);

	WriteBothBuffer(_pos.X + 4, _pos.Y - 4, "         ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 3, " MUYAHO! ");
	WriteBothBuffer(_pos.X + 4, _pos.Y - 2, "         ");
}

void ShowGameover(void)
{
	ShowLoadingBuffer("Game Over...");
	PlaySound(TEXT("Gameover.wav"), 0, SND_FILENAME | SND_ASYNC);
}

void ShowGameClear(void)
{
	ShowLoadingBuffer("Game Clear!!!");
	PlaySound(TEXT("GameClear.wav"), 0, SND_FILENAME | SND_ASYNC);
}

void ShowStageLoading(const int stage)
{
	if (stage == 0)
		ShowLoadingBuffer("Now Loading...");
	else if (stage == STAGE_LAST)
		ShowLoadingBuffer("FINAL STAGE");
	else
		ShowLoadingBuffer("STAGE " + std::to_string(stage));
}
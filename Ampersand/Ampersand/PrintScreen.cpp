#include "PrintScreen.h"

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
#include "CoordData.h"

coord WorldToScreen(const int x, const int y)
{
	coord ret = { y, x + 12 };
	return ret;
}

coord WorldToScreen(const coord &pos)
{
	coord ret = { pos.y, pos.x + 12 };
	return ret;
}
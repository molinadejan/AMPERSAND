#include "CoordData.h"

COORD WorldToScreen(const SHORT &x, const SHORT &y)
{
	COORD ret = { y, x + 12 };
	return ret;
}

COORD WorldToScreen(const COORD &pos)
{
	COORD ret = { pos.Y, pos.X + 12 };
	return ret;
}
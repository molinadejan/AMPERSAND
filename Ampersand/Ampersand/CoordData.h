#pragma once

#include "InitSettings.h"

typedef struct _coord
{
	int x;
	int y;
} coord;

coord WorldToScreen(const int x, const int y);
coord WorldToScreen(const coord &pos);

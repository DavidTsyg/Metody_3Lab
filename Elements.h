#pragma once
static const int ROWS = 4;
static const int COLUMNS = 4;
static double x[ROWS - 1][COLUMNS - 1] = {
	{ 2, 1, 1 },
	{ 1, 2, 0 },
	{ 0, 0.5, 4 }
};
static double c[ROWS - 1] = { 7, 7, 6 };
static double b[COLUMNS - 1] = { 8, 2, 6 };
#pragma once

#include <stdio.h>

const int arrayMaxW = 1920 / 8 + 5;
const int arrayMaxH = 1080 / 8 + 5;

class Cells
{
public:
	Cells();
	~Cells();

	void LoadArray(FILE* arrayFile);
	void UpdateArray();
	void PrintCurrentGeneration();

private:
	int cellSize = 8;

	int generation = 0;

	int arrayW = 0;
	int arrayH = 0;
	int cellArray[arrayMaxW][arrayMaxH] = { 0 };
};


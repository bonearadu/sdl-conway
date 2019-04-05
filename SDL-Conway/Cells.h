#pragma once

#include <stdio.h>
#include "SDL.h"

const int arrayMaxW = 1920 / 8 + 5;
const int arrayMaxH = 1080 / 8 + 5;

class Cells
{
public:
	Cells(int windowW, int windowH);
	~Cells();

	void LoadArray(FILE* arrayFile);
	void UpdateArray();
	void PrintCurrentGeneration(SDL_Renderer* ren);

private:
	int cellSize = 8;

	int generation = 0;

	int arrayW = 0;
	int arrayH = 0;
	bool cellArray[arrayMaxH][arrayMaxW] = { 0 };

	SDL_Rect cell;
};
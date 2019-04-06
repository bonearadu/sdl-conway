#pragma once

#include "SDL.h"

const int arrayMaxW = 1920 / 8 + 5;
const int arrayMaxH = 1080 / 8 + 5;

class Cells
{
public:
	int arrayW = 0;
	int arrayH = 0;

	Cells(int windowW, int windowH);
	~Cells();

	void LoadArray(const char* fileName);
	void PrintArray();
	void UpdateArray();
	void PrintCurrentGeneration(SDL_Renderer* ren);
	void PrintGrid(SDL_Renderer* ren);
	void GenRandomArray(int arrH, int arrW, const char* fileName);

private:
	int cellSize = 8;
	int cellSpace = 1;
	int generation = 0;
	bool cellArray[arrayMaxH][arrayMaxW] = { 0 };

	SDL_Rect cell;
};
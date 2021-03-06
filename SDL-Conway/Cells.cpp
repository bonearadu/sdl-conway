#include "Cells.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool tempArr[arrayMaxH][arrayMaxW];

void cleanTempArr()
{
	for (int i = 0; i < arrayMaxH; i++)
		for (int j = 0; j < arrayMaxW; j++)
			tempArr[i][j] = 0;
}

Cells::Cells(int windowW, int windowH)
{
	arrayW = windowW / cellSize;
	arrayH = windowH / cellSize;

	cell.w = cellSize - cellSpace;
	cell.h = cellSize - cellSpace;
}

Cells::~Cells()
{}

void Cells::LoadArray(const char* fileName)
{	
	FILE* arrayFile = 0;
	fopen_s(&arrayFile, fileName, "r");

	if (arrayFile != 0)
	{
		int arrW, arrH, temp;

		fscanf_s(arrayFile, "%d %d", &arrH, &arrW);

		if (arrW <= arrayW && arrH <= arrayH)
		{
			for (int i = 1; i <= arrH; i++)
			{
				for (int j = 1; j <= arrW; j++)
				{
					fscanf_s(arrayFile, "%d", &temp);
					cellArray[i][j] = temp;
				}
			}

			printf_s("Cell Array successfully loaded!\n");
		}
		else printf_s("ERROR: Invalid array dimensions! %d %d\n", arrH, arrW);

		fclose(arrayFile);
	}
	else printf_s("ERROR: Cannot open file %s!\n", fileName);
}

void Cells::UpdateArray()
{
	int tempSum;
	
	int direction[8][2] = { -1,-1, -1,0, -1,1, 0,-1, 0,1, 1,-1, 1,0, 1,1 };

	for (int i = 1; i <= arrayH + 1; i++)
		for (int j = 1; j <= arrayW + 1; j++)
		{
			tempSum = 0;

			for (int k = 0; k < 8; k++)
				tempSum += cellArray[i + direction[k][0]][j + direction[k][1]];

			if (cellArray[i][j])
			{
				if (tempSum > 3) tempArr[i][j] = false;
				else if (tempSum == 2 || tempSum == 3) tempArr[i][j] = true;
				else if (tempSum < 2) tempArr[i][j] = false;
			}
			else if (tempSum == 3) tempArr[i][j] = true;
		}

	for (int i = 1; i <= arrayH + 1; i++)
		for (int j = 1; j <= arrayW + 1; j++)
			cellArray[i][j] = tempArr[i][j];

	cleanTempArr();
}

void Cells::GenRandomArray(int arrH, int arrW, const char* fileName)
{
	FILE* out = 0;
	fopen_s(&out, fileName, "w");

	if (out != 0)
	{
		srand(time(NULL));

		fprintf_s(out, "%d %d\n", arrH, arrW);

		for (int i = 1; i <= arrH; i++)
		{
			for (int j = 1; j <= arrW; j++)
				fprintf_s(out, "%d ", rand() % 2);

			fprintf_s(out, "\n");
		}

		printf_s("Random array generated!\n");

		fclose(out);
	}
	else printf_s("ERROR: Cannot open file %s!\n", fileName);
}

void Cells::PrintCurrentGeneration(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

	for (int i = 1; i <= arrayH; i++)
		for (int j = 1; j <= arrayW; j++)
			if (cellArray[i][j])
			{
				cell.x = (j - 1) * cellSize + cellSpace;
				cell.y = (i - 1) * cellSize + cellSpace;

				SDL_RenderFillRect(ren, &cell);
				SDL_RenderDrawRect(ren, &cell);
			}

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void Cells::PrintArray()
{
	for (int i = 1; i <= arrayH; i++)
	{
		for (int j = 1; j <= arrayW; j++)
			printf_s("%d ", cellArray[i][j]);

		printf_s("\n");
	}
}

void Cells::PrintGrid(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 31, 31, 31, 255);

	for (int i = 1; i <= arrayH; i++)
	{
		SDL_RenderDrawLine(ren, 0, i * cellSize, arrayW * cellSize, i * cellSize);
	}

	for (int i = 1; i <= arrayW; i++)
	{
		SDL_RenderDrawLine(ren, i * cellSize, 0, i * cellSize, arrayH * cellSize);
	}

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}
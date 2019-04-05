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

	cell.w = cellSize;
	cell.h = cellSize;
}

Cells::~Cells()
{}

void Cells::LoadArray(const char* fileName)
{	
	FILE* arrayFile;
	fopen_s(&arrayFile, fileName, "r");

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
	else printf_s("ERROR: Invalid array dimensions! %d %d\n", arrW, arrH);

	fclose(arrayFile);
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
	FILE* out;
	fopen_s(&out, fileName, "w");

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

void Cells::PrintCurrentGeneration(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

	for (int i = 1; i <= arrayH; i++)
		for (int j = 1; j <= arrayW; j++)
			if (cellArray[i][j])
			{
				cell.y = (j - 1) * 8;
				cell.x = (i - 1) * 8;

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
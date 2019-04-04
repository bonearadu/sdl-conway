#include "Cells.h"

Cells::Cells()
{}

Cells::~Cells()
{}

void Cells::LoadArray(FILE* arrayFile)
{
	int arrW, arrH;

	scanf_s("%d %d", &arrW, &arrH);

	if (arrW <= arrayMaxW && arrH < arrayMaxH)
	{
		arrayW = arrW;
		arrayH = arrH;

		for (int i = 1; i <= arrayW; i++)
			for (int j = 1; j <= arrayH; j++)
				scanf_s("%d", &cellArray[i][j]);

		printf_s("Cell Array successfully loaded!\n");
	}
	else printf_s("ERROR: Invalid array dimensions!\n");
}

void Cells::UpdateArray()
{
	int tempArr[arrayMaxH][arrayMaxW], tempSum;

	int direction[8][2] = { -1,-1, -1,0, -1,1, 0,-1, 0,1, 1,-1, 1,0, 1,1 };

	for (int i = 1; i <= arrayW; i++)
		for (int j = 1; j <= arrayH; j++)
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
			else if (tempSum == 3) tempSum[i][j] = true;
		}

	for (int i = 1; i <= arrayW; i++)
		for (int j = 1; j <= arrayH; j++)
			cellArray[i][j] = tempArr[i][j];
}

void Cells::PrintCurrentGeneration()
{
	// to be implemented
}
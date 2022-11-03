#include "fillTable.h"
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

MPS_tool::MPS_tool() { }

int MPS_tool::solveMPS(const int& start, const int& end)
{
	// printf("start: %d, end: %d\n", start, end);
	if(isUpdated[start][end])
		return maxTable[start][end];

	isUpdated[start][end] = true;
	if(start >= end)
	{
		return maxTable[start][end] = 0;
	}
	if(line_arr[start] == end)
	{
		recordTable[start][end] = 1; //case 1 start-end is a chord
		return maxTable[start][end] = 1 + solveMPS(start + 1, end - 1);
	}
	const int k = line_arr[end];
	const int v3 = solveMPS(start, end - 1);
	if(k > start && k < end)
	{
		const int v2 = 1 + solveMPS(start, k - 1) + solveMPS(k + 1, end - 1);
		if(v2 > v3)
		{
			recordTable[start][end] = 2; //case 2
			return maxTable[start][end] = v2;
		}
	}
	recordTable[start][end] = 3; //case 3 k-end is a chord, k is outside start-end
	return maxTable[start][end] = v3;
};
void MPS_tool::traceAnswer(const int start, const int end)
{
	if(start == end)
		return;
	if(recordTable[start][end] == 1)
	{
		ansline.push_back(start);
		traceAnswer(start + 1, end - 1);
	}
	else if(recordTable[start][end] == 2)
	{
		const int k = line_arr[end];
		ansline.push_back(k);
		traceAnswer(start, k - 1);
		traceAnswer(k + 1, end - 1);
	}
	else
	{
		traceAnswer(start, end - 1);
	}
}
#include "fillTable.h"
#include <iostream>
#include <limits>
#include <math.h>
#include <stdlib.h>

using namespace std;

void fillTable(const int start, const int end, int** maxTable, int* line_arr)
{
	if(start == end)
	{
		maxTable[start][end] = 0;
	}
	else if(line_arr[start] == end)
	{
		maxTable[start][end] = 1 + maxTable[start + 1][end - 1];
	}
	else
	{
		const int k = line_arr[end];
		if(k > start && k < end)
		{
			maxTable[start][end] = max(1 + maxTable[start][k - 1] + maxTable[k + 1][end - 1],
									   maxTable[start][end - 1]);
		}
		else
		{
			maxTable[start][end] = maxTable[start][end - 1];
		}
	}
	// cout << "maxTable value : " << maxTable[start][end] << endl;
};
#include "fillTable.h"
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

MPS_tool::MPS_tool() { }

int MPS_tool::fillTable(const int& start, const int& end)
{

	if(maxTable[start][end] != -1)
		return maxTable[start][end];

	if(line_arr[start] == end) // start - end is a chord
	{
		recordTable[start][end] = 1; //case 1
		return maxTable[start][end] = (1 + fillTable(start + 1, end - 1));
	}
	else
	{
		const int k = line_arr[end];
		const int kj_line_out = fillTable(start, end - 1);

		if(k > start && k < end) //exist k s.t. k-end is a chord and k is between start and end
		{
			const int kj_line_in = 1 + fillTable(start, k - 1) + fillTable(k + 1, end - 1);
			if(kj_line_in > kj_line_out)
			{
				recordTable[start][end] = 2; //case 2
				return maxTable[start][end] = kj_line_in;
			}
		}
		//exist k s.t. k-end is a chord and k is outside start and end
		recordTable[start][end] = 3; //case 3
		return maxTable[start][end] = kj_line_out;
	}
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
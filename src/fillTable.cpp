#include "fillTable.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define Value_BITS 1048575u
#define IsUPDATED_BITS 4194304u
#define TYPE1 1048576u
#define TYPE2 2097152u
#define TYPE3 3145728u

MPS_tool::MPS_tool() { }

int MPS_tool::solveMPS(const int& start, const int& end)
{
	// printf("start: %d, end: %d \n", start, end);
	if(solutionTable[start][end] & IsUPDATED_BITS)
		return solutionTable[start][end];

	if(start >= end)
	{
		return solutionTable[start][end] = 0 | IsUPDATED_BITS;
	};
	uint value;
	uint type;
	const uint k = line_arr[end];
	if(k == start)
	{
		value = (solveMPS(start + 1, end - 1) & Value_BITS) + 1;
		type = TYPE1;
	}
	else
	{
		const uint v3 = solveMPS(start, end - 1) & Value_BITS;
		if(k > start && k < end)
		{
			const uint v2 =
				1 + (solveMPS(start, k - 1) & Value_BITS) + (solveMPS(k + 1, end - 1) & Value_BITS);
			if(v2 > v3)
			{
				value = v2;
				type = TYPE2;
			}
			else
			{
				value = v3;
				type = TYPE3;
			}
		}
		else
		{
			value = v3;
			type = TYPE3; //case 3 k-end is a chord, k is outside start-end
		}
	}

	return solutionTable[start][end] = value | type | IsUPDATED_BITS;
};
void MPS_tool::traceAnswer(const int start, const int end)
{
	if(start == end)
		return;
	uint type = (solutionTable[start][end] & (TYPE3)) >> 20u;
	if(type == 1)
	{
		fout << start << " " << line_arr[start] << endl;
		traceAnswer(start + 1, end - 1);
	}
	else if(type == 2)
	{
		const int k = line_arr[end];
		traceAnswer(start, k - 1);
		fout << k << " " << line_arr[k] << endl;
		traceAnswer(k + 1, end - 1);
	}
	else if(type == 3)
	{
		traceAnswer(start, end - 1);
	}
	else
	{
		return;
	}
}
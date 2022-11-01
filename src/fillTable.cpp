#include "fillTable.h"
#include <iostream>
#include <limits>
#include <math.h>
#include <stdlib.h>
// #include <vector>

// using namespace std;
void print_vector(const vector<int> v)
{
	for(int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
};
void fillTable(
	const int start, const int end, int** maxTable, int* line_arr, vector<int>** recordTable)
{
	if(start == end)
	{
		maxTable[start][end] = 0;
	}
	else if(line_arr[start] == end)
	{
		maxTable[start][end] = 1 + maxTable[start + 1][end - 1];
		vector<int> v = recordTable[start + 1][end - 1];
		v.push_back(start);
		print_vector(v);
		recordTable[start][end] = v;
	}
	else
	{
		const int k = line_arr[end];
		if(k > start && k < end)
		{
			int kj_line_in = 1 + maxTable[start][k - 1] + maxTable[k + 1][end - 1];
			int kj_line_out = maxTable[start][end - 1];
			if(kj_line_in > kj_line_out)
			{
				maxTable[start][end] = kj_line_in;

				//concatenate the two vectors
				vector<int> v = recordTable[start][k - 1];
				v.insert(v.end(),
						 recordTable[k + 1][end - 1].begin(),
						 recordTable[k + 1][end - 1].end());
				v.push_back(k);
				print_vector(v);
				recordTable[start][end] = v;
			}
			else
			{
				maxTable[start][end] = kj_line_out;
			}
		}
		else
		{
			maxTable[start][end] = maxTable[start][end - 1];
		}
	}
	// cout << "maxTable value : " << maxTable[start][end] << endl;
};
// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "../lib/tm_usage.h"
#include "fillTable.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

void help_message()
{
	cout << "usage: MPS - <input_file> <output_file>" << endl;
}
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		help_message();
		return 0;
	}
	CommonNs::TmUsage tmusg;
	CommonNs::TmStat stat;
	///////// set timer //////////
	time_t t1, t2;
	t1 = time(NULL);

	//////////// read the input file /////////////
	fstream fin(argv[1]);
	fstream fout;
	fout.open(argv[2], ios::out);
	int num_vertices = 0;
	int line_number = 0;
	fin >> num_vertices;
	int* line_arr = new int[num_vertices];
	int num_line = num_vertices / 2;
	//////////// initiate variables /////////////
	cout << "reading input" << endl;
	for(int i = 0; i < num_line; i++)
	{
		int v1;
		int v2;
		fin >> v1;
		fin >> v2;
		line_arr[v1] = v2;
		line_arr[v2] = v1;
	}

	cout << "initialize table" << endl;
	vector<vector<unsigned int>> maxTable(num_vertices,
										  vector<unsigned int>(num_vertices)); // 2D vector
	vector<int>** recordTable = new vector<int>*[num_vertices];

	////////////// fill the max table //////////////
	cout << "filling table" << endl;
	for(int end = 1; end < num_vertices; end++)
	{
		for(int start = 0; start < end; start++)
		{
			// fillTable(i, j, maxTable, line_arr, recordTable);
			if(start % 1000 == 0 && end % 1000 == 0)
			{
				cout << "start: " << start << " end: " << end << endl;
			}

			if(line_arr[start] == end) // start - end is a chord
			{
				maxTable[start][end] = 1 + maxTable[start + 1][end - 1];
				// vector<int> v = recordTable[start + 1][end - 1];
				// v.push_back(start);
				// recordTable[start][end] = v;
			}
			else
			{
				const unsigned int k = line_arr[end];
				if(k > start &&
				   k < end) //exist k s.t. k-end is a chord and k is between start and end
				{
					const unsigned int kj_line_in =
						1 + maxTable[start][k - 1] + maxTable[k + 1][end - 1];
					const unsigned int kj_line_out = maxTable[start][end - 1];
					if(kj_line_in > kj_line_out)
					{
						maxTable[start][end] = kj_line_in;
					}
					else
					{
						maxTable[start][end] = kj_line_out;
						// recordTable[start][end] = recordTable[start][end - 1];
					}
				}
				else //exist k s.t. k-end is a chord and k is outside start and end
				{
					maxTable[start][end] = maxTable[start][end - 1];
					// recordTable[start][end] = recordTable[start][end - 1];
				}
			}
		}
	}

	tmusg.periodStart();
	tmusg.getPeriodUsage(stat);
	t2 = time(NULL);
	cout << "Total time: " << t2 - t1 << " secs\n";
	// cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
	cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

	//////////// write the output file ///////////
	fout << maxTable[0][num_vertices - 1] << endl;
	// vector<int> result = recordTable[0][num_vertices - 1];
	// std::sort(result.begin(), result.end());
	// cout << result.size() << endl;
	// for(int i = 0; i < result.size(); i++)
	// {
	// 	fout << result[i] << " " << line_arr[result[i]] << endl;
	// }
	fin.close();
	fout.close();
	return 0;
}

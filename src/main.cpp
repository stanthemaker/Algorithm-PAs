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
	for(int i = 0; i < num_line; i++)
	{
		int v1;
		int v2;
		fin >> v1;
		fin >> v2;
		line_arr[v1] = v2;
		line_arr[v2] = v1;
	}

	int** maxTable = new int*[num_vertices];
	vector<int>** recordTable = new vector<int>*[num_vertices];
	cout << "initialize table" << endl;

	for(int i = 0; i < num_vertices; ++i)
	{
		if(i % 1000 == 0)
			cout << "i = " << i << "\n";
		maxTable[i] = new int[num_vertices];
		memset(maxTable[i], -1, sizeof(int) * num_vertices); // initialize to 0 is better
		maxTable[i][i] = 0;

		recordTable[i] = new vector<int>[num_vertices];
	}

	////////////// fill the max table //////////////
	cout << "filling table" << endl;
	for(int j = 1; j < num_vertices; j++)
	{
		for(int i = 0; i < j; i++)
		{
			fillTable(i, j, maxTable, line_arr, recordTable);
		}
	}

	tmusg.periodStart();
	tmusg.getPeriodUsage(stat);
	cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
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

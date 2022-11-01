// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "../lib/tm_usage.h"
#include "fillTable.h"
#include <cstring>
#include <fstream>
#include <iostream>
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
	bool* reverseTable = new bool[num_vertices];
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
		reverseTable[v1] = false;
		reverseTable[v2] = true;
	}

	int** maxTable = new int*[num_vertices];
	for(int i = 0; i < num_vertices; ++i)
	{
		maxTable[i] = new int[num_vertices];
		memset(maxTable[i], -1, sizeof(int) * num_vertices);
		maxTable[i][i] = 0;
	}

	////////////// fill the max table //////////////
	for(int j = 1; j < num_vertices; j++)
	{
		for(int i = 0; i < j; i++)
		{
			fillTable(i, j, maxTable, line_arr);
		}
	}
	tmusg.periodStart();
	tmusg.getPeriodUsage(stat);
	cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
	cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

	//////////// write the output file ///////////
	fout << maxTable[0][num_vertices - 1] << endl;
	// fout << "# " << data.size() << " data points" << endl;
	// fout << "# index number" << endl;
	// for (int i = 0; i < data.size(); i++)
	//     fout << i << " " << data[i] << endl;
	fin.close();
	fout.close();
	return 0;
}

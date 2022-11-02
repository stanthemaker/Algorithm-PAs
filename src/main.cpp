// #include "../lib/tm_usage.h"
#include "fillTable.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
	time_t t1, t2;
	t1 = time(NULL);

	//////////// read the input file /////////////
	cout << "reading input" << endl;
	FILE* input_file = fopen(argv[1], "r");
	fstream fout;
	fout.open(argv[2], ios::out);
	int num_vertices;
	fscanf(input_file, "%d", &num_vertices);
	const int num_line = num_vertices >> 1;

	//////////// initiate variables /////////////
	MPS_tool MPS;
	MPS.line_arr = new int[num_vertices];
	for(int i = 0; i < num_line; i++)
	{
		int v1;
		int v2;
		fscanf(input_file, "%d %d", &v1, &v2);
		MPS.line_arr[v1] = v2;
		MPS.line_arr[v2] = v1;
	}
	fclose(input_file);

	cout << "initialize table" << endl;
	MPS.ansline.reserve(num_vertices);
	////////////// fill the max table //////////////
	cout << "filling table" << endl;
	const int ans = MPS.solveMPS(0, num_vertices - 1);
	MPS.traceAnswer(0, num_vertices - 1);

	t2 = time(NULL);
	cout << "Total time: " << t2 - t1 << " secs\n";

	//////////// write the output file ///////////
	fout << ans << endl;
	std::sort(MPS.ansline.begin(), MPS.ansline.end());
	for(int i = 0; i < MPS.ansline.size(); i++)
	{
		fout << MPS.ansline[i] << " " << MPS.line_arr[MPS.ansline[i]] << endl;
	}
	fout.close();
	return 0;
}

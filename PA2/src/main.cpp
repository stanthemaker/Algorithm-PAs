// #include "../lib/tm_usage.h"
#include "fillTable.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
#define Value_BITS 1048575u

MPS_tool MPS;

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
	printf("Reading input file...\n");
	FILE* input_file = fopen(argv[1], "r");
	MPS.fout.open(argv[2], ios::out);
	int num_vertices;
	fscanf(input_file, "%d", &num_vertices);
	const int num_line = num_vertices >> 1;

	for(int i = 0; i < MAX_VERTICES; i++)
	{
		MPS.solutionTable[i] = new uint[MAX_VERTICES];
	}

	// //////////// initiate variables /////////////
	printf("initiate variables...\n");
	MPS.line_arr = new uint[num_vertices];
	for(int i = 0; i < num_line; i++)
	{
		uint v1;
		uint v2;
		fscanf(input_file, "%d %d", &v1, &v2);
		MPS.line_arr[v1] = v2;
		MPS.line_arr[v2] = v1;
	}
	fclose(input_file);

	////////////// fill the max table //////////////
	printf("filling table...\n");
	const int ans = MPS.solveMPS(0, num_vertices - 1) & Value_BITS;
	MPS.fout << ans << endl;

	printf("Tracing anwser..\n");
	MPS.traceAnswer(0, num_vertices - 1);

	t2 = time(NULL);
	printf("total time cost: %ld secs\n", t2 - t1);
	//////////// write the output file ///////////
	MPS.fout.close();

	return 0;
}

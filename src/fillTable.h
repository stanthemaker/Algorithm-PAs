#ifndef MSP_tool
#define MSP_tool
#define MAX_VERTICES 180000
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
class MPS_tool
{
public:
	MPS_tool(); // constructor
	int solveMPS(const int&, const int&);
	void traceAnswer(const int, const int);
	fstream fout;
	uint* solutionTable[MAX_VERTICES];
	uint* line_arr;
	vector<int> ansline;
};

// int fillTable(const int start, const int end, int** maxTable, int* line_arr);
#endif
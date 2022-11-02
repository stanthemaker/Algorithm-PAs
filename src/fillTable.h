#ifndef MSP_tool
#define MSP_tool
#include <vector>
using namespace std;

void fillTable(const int start,
			   const int end,
			   vector<vector<int>>& maxTable,
			   int* line_arr,
			   vector<int>** recordTable);
#endif
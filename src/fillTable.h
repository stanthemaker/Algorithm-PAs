#ifndef MSP_tool
#define MSP_tool
#define MAX_VERTICES 180000
#include <vector>

using namespace std;
class MPS_tool
{
public:
	MPS_tool(); // constructor
	int fillTable(const int&, const int&);
	void traceAnswer(const int, const int);
	int** maxTable;
	int* line_arr;
	int** recordTable;
	vector<int> ansline;
};

// int fillTable(const int start, const int end, int** maxTable, int* line_arr);
#endif
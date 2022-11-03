#ifndef MSP_tool
#define MSP_tool
#define MAX_VERTICES 180000
#include <vector>

using namespace std;
class MPS_tool
{
public:
	MPS_tool(); // constructor
	int solveMPS(const int&, const int&);
	void traceAnswer(const int, const int);
	int* line_arr;
	vector<int> ansline;

	// private:
	// bool isUpdated[MAX_VERTICES][MAX_VERTICES];
	// int maxTable[MAX_VERTICES][MAX_VERTICES];
	// int recordTable[MAX_VERTICES][MAX_VERTICES];
	bool* isUpdated[MAX_VERTICES];
	int* maxTable[MAX_VERTICES];
	int* recordTable[MAX_VERTICES];
};

// int fillTable(const int start, const int end, int** maxTable, int* line_arr);
#endif
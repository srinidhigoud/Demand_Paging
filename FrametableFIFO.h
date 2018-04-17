#ifndef FRAMEFIFO_H
#define FRAMEFIFO_H
#include "Frametable.h"
#include "Process.h"
#include "Random.h"

#include <vector>
#include <deque>
using namespace std;
class FrametableFIFO: public Frametable{
public:
	FrametableFIFO(char* argv[]);
	int numberOfFrames;
	deque<vector<int> > frametable;
	bool pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime);//checks if there are page faults, return true if a page fault
	void pageReplacement(vector<Process>& processes, int pagenumber, int processnumber, int currenttime, Random* random);//replaces frames accroding to the algorithm FIFO
};
#endif
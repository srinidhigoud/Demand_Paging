#ifndef FRAME_H
#define FRAME_H
#include "Process.h"
#include "Random.h"

#include <vector>
using namespace std;
class Frametable{
public:
	Frametable(){}
	int printcheck;
	virtual bool pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime) = 0;//checks if there are page faults, return true if a page fault
	virtual void pageReplacement(vector<Process>& processes, int pagenumber, int processnumber, int currenttime, Random* random) = 0;//replaces frames accroding to the algorithm 
};
#endif
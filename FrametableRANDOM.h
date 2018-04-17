#ifndef FRAMERANDOM_H
#define FRAMERANDOM_H
#include "Frametable.h"
#include "Process.h"
#include "Random.h"

#include <vector>
#include <deque>
using namespace std;
class FrametableRANDOM: public Frametable{
public:
	FrametableRANDOM(char* argv[]);
	int numberOfFrames;
	int **frametable;
	bool pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime);//checks if there are page faults, return true if a page fault
	void pageReplacement(vector<Process>& processes, int pagenumber, int processnumber, int currenttime, Random* random);//replaces frames accroding to the algorithm RANDOM
};
#endif
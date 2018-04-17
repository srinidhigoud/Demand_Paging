#ifndef FRAMELRU_H
#define FRAMELRU_H
#include "Frametable.h"
#include "Process.h"
#include <vector>
#include <deque>
using namespace std;
class FrametableLRU: public Frametable{
public:
	FrametableLRU(char* argv[]);
	int numberOfFrames;
	deque<vector<int> > frametable;
	bool pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime);
	void pageReplacement(vector<Process>& processes, int pagenumber, int processnumber, int currenttime, Random* random);
};
#endif
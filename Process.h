#ifndef PROCESS_H
#define PROCESS_H
#include "Random.h"
using namespace std;

class Process{
public:
	int quantum;
	int referenceSize;
	int residencytime;
	int evictioncount;
	int faultcount;
	int nextWord;
	int processSize;
	Process(int processSize, int processnumber, int referenceSize);
	bool hasended();
	bool hasfinishedquantum();
	void nextreference(double A, double B, double C, Random* rand);
	int getnextWord();
};
#endif
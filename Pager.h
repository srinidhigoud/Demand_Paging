#ifndef PAGER_H
#define PAGER_H
#include "Frametable.h"
#include "Process.h"
#include "Random.h"
#include <vector>
#include <string>
using namespace std;
class Pager{
public:
	vector<Process> processes;
	int machineSize;
	int pageSize;
	int processSize;
	int jobMix;
	int referenceNumber;
	int printcheck;
	Random* random;
	Frametable* frametable;
	string algorithm;
	Pager(char* argv[], Frametable* frametable, Random* rand);
	void run();
	void print();
};
#endif
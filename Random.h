#ifndef RANDOM_H
#define RANDOM_H
#include <string>
using namespace std;

class Random{
public:
	int k;
	string filename;
	Random(char* argv[]);
	void reset();
	int get();
	bool printcheck;
};
#endif

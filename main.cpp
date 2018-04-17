
/***************************************************

	Srinidhi Goud Myadaboyina
	N12449860	
	Lab 4


***************************************************/



#include <iostream>
#include <string>
using namespace std;
#include "Frametable.h"
#include "FrametableFIFO.h"
#include "FrametableLRU.h"
#include "FrametableRANDOM.h"
#include "Pager.h"
#include "Random.h"

int main(int argc, char* argv[]){
	cout<<endl;
	string ss(argv[6]);
	Random* random = new Random(argv);//create a random class objects that reads sequentially
	Frametable* frame;
	if(ss.compare("lru")==0) frame = new FrametableLRU(argv);
	else if(ss.compare("fifo")==0) frame = new FrametableFIFO(argv);
	else if(ss.compare("random")==0) frame = new FrametableRANDOM(argv);
	Pager* p = new Pager(argv,frame, random);
	p->run();
	p->print();
	random->reset();
}

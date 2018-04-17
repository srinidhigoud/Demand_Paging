#include "FrametableFIFO.h"
#include <iostream>
#include <string>
FrametableFIFO::FrametableFIFO(char* argv[]){
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));//Machine size by page size
	printcheck = stoi(string(argv[7]));//7th argument for controlling way of printing
}

bool FrametableFIFO::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){ //checks if there are page faults, return true if a page fault
	for(int i=0;i<frametable.size();i++) if(frametable[i][0] == pagenumber && frametable[i][1] == processnumber){
		if(printcheck>0) cout<<"The process number "<<processnumber<<" has a hit at frame "<<i<<" at run time "<<runtime<<endl;
		return false;
	} 
	if(printcheck>0) cout<<"The process number "<<processnumber<<" has a fault at "<<runtime<<endl;
	processes[processnumber-1].faultcount++;//increase fault count
	return true;
}

void FrametableFIFO::pageReplacement(vector<Process>& processes,int pagenumber, int processnumber, int currenttime, Random* random){//replaces frames accroding to the algorithm FIFO
	//maintains a queue, addds and removes in fifo order
	if(numberOfFrames == frametable.size()){//if queue is full, evict a frame based on the priority
		vector<int> buf(frametable[0]);
		processes[buf[1]-1].residencytime += currenttime - buf[2];//add to running sum, the residency time
		processes[buf[1]-1].evictioncount++;//increase eviction count
		frametable.pop_front();
	}
	frametable.push_back(vector<int>{pagenumber,processnumber,currenttime});
}
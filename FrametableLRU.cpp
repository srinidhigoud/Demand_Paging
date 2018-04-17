#include "FrametableLRU.h"
#include <iostream>
#include <algorithm>
FrametableLRU::FrametableLRU(char* argv[]){
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));//Machine size by page size
	printcheck = stoi(string(argv[7]));//7th argument for controlling way of printing
}

bool FrametableLRU::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){//checks if there are page faults, return true if a page fault
	for(int i=0;i<frametable.size();i++){
		if(frametable[i][0] == pagenumber && frametable[i][1] == processnumber){
			if(printcheck>0) cout<<"The process number "<<processnumber<<" has a hit at frame "<<i<<" at run time "<<runtime<<endl;
			frametable[i][3] = runtime;
			return false;
		} 
	} 
	if(printcheck>0) cout<<"The process number "<<processnumber<<" has a fault at "<<runtime<<endl;
	processes[processnumber-1].faultcount++;//increase fault count
	return true;
}

void FrametableLRU::pageReplacement(vector<Process>& processes,int pagenumber, int processnumber, int currenttime, Random* random){//replaces frames accroding to the algorithm LRU
	//maintain a priority queue
	int leastReferencedTime = currenttime;
	int evictedframe = 0;
	auto comp = [](vector<int> a, vector<int> b){return a[a.size()-1]<b[b.size()-1];};
	sort(frametable.begin(),frametable.end(),comp);//sort it as there are multiple references changing the loading time
	if(frametable.size()== numberOfFrames){
		int  evictedprocess = frametable[0][1];
		int evictedprocTime = frametable[0][2];
		frametable.pop_front();
		processes[evictedprocess-1].residencytime += currenttime - evictedprocTime;//add to running sum, the residency time
		processes[evictedprocess-1].evictioncount++;//increase eviction count
		frametable.push_back(vector<int> {pagenumber,processnumber,currenttime,currenttime});//push it at the end of the priority queue as the recent time is the highest
		return;
	}
	//if not found just push it at the end
	frametable.push_back(vector<int> {pagenumber,processnumber,currenttime,currenttime});//push it at the end of the priority queue as the recent time is the highest

}
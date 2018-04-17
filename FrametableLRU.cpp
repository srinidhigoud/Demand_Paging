#include "FrametableLRU.h"
#include <iostream>
#include <algorithm>
FrametableLRU::FrametableLRU(char* argv[]){
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));//Machine size by page size
	printcheck = stoi(string(argv[7]));//7th argument for controlling way of printing
	frametable = (int**)malloc(numberOfFrames*sizeof(int*));//allocate frame table so as to allocated from higher frames
	for(int i=0;i<numberOfFrames;i++){
		frametable[i] = (int*)malloc(4*sizeof(int));
		for(int j=0;j<4;j++) frametable[i][j] = 0;
	} 
}

bool FrametableLRU::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){//checks if there are page faults, return true if a page fault
	for(int i=0;i<numberOfFrames;i++){
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

	int leastReferencedTime = currenttime;
	int evictedframe = 0;

	for(int i=numberOfFrames-1;i>=0;i--){//iterates from the higher end to find a free frame
		if((frametable[i][0]==0)&&(frametable[i][1]==0)){
			frametable[i][0] = pagenumber;
			frametable[i][1] = processnumber;
			frametable[i][2] = currenttime;
			frametable[i][3] = currenttime;
			return;
		}
		else if(leastReferencedTime>frametable[i][3]){//if not found a free frame eviction is needed
			leastReferencedTime = frametable[i][3];
			evictedframe = i;
		}
	}
	
	int evictedprocess = frametable[evictedframe][1];
	int evictedprocTime = frametable[evictedframe][2];
	processes[evictedprocess-1].residencytime += currenttime - evictedprocTime;//add to running sum, the residency time
	processes[evictedprocess-1].evictioncount++;//increase eviction count
	frametable[evictedframe][0] = pagenumber;
	frametable[evictedframe][1] = processnumber;
	frametable[evictedframe][2] = currenttime;
	frametable[evictedframe][3] = currenttime;
}
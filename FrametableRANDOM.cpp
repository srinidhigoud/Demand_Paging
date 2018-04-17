#include "FrametableRANDOM.h"
#include <iostream>
FrametableRANDOM::FrametableRANDOM(char* argv[]){
	printcheck = stoi(string(argv[7]));//7th argument for controlling way of printing
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));//Machine size by page size
	frametable = (int**)malloc(numberOfFrames*sizeof(int*));//allocate frame table so as to allocated from higher frames
	for(int i=0;i<numberOfFrames;i++){
		frametable[i] = (int*)malloc(4*sizeof(int));
		for(int j=0;j<4;j++) frametable[i][j] = 0;
	} 
}

bool FrametableRANDOM::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){//checks if there are page faults, return true if a page fault
	for(int i=0;i<numberOfFrames;i++) if(frametable[i][0] == pagenumber && frametable[i][1] == processnumber){
		if(printcheck>0) cout<<"The process number "<<processnumber<<" has a hit at frame "<<i<<" at run time "<<runtime<<endl;
		return false;
	} 
	if(printcheck>0) cout<<"The process number "<<processnumber<<" has a fault at "<<runtime<<endl;
	processes[processnumber-1].faultcount++;//increase fault count
	return true;
}

void FrametableRANDOM::pageReplacement(vector<Process>& processes,int pagenumber, int processnumber, int currenttime, Random* random){//replaces frames accroding to the algorithm RANDOM
	for(int i=numberOfFrames-1;i>=0;i--){//iterates from the higher end to find a free frame
		if((frametable[i][0]==0)&&(frametable[i][1]==0)){
			frametable[i][0] = pagenumber;
			frametable[i][1] = processnumber;
			frametable[i][2] = currenttime;
			return;
		}
	}
	//if not found a free frame eviction is needed
	int randomNumber = random->get();
	int evictedframe = randomNumber%numberOfFrames;//randomly find the frame number to be evicted
	int evictedprocess = frametable[evictedframe][1];
	int evictedprocTime = frametable[evictedframe][2];
	processes[evictedprocess-1].residencytime += currenttime - evictedprocTime;//add to running sum, the residency time
	processes[evictedprocess-1].evictioncount++;//increase eviction count
	frametable[evictedframe][0] = pagenumber;
	frametable[evictedframe][1] = processnumber;
	frametable[evictedframe][2] = currenttime;
}
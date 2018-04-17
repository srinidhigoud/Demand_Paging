#include "FrametableRANDOM.h"
#include <iostream>
FrametableRANDOM::FrametableRANDOM(char* argv[]){
	printcheck = stoi(string(argv[7]));
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));
	frametable = (int**)malloc(numberOfFrames*sizeof(int*));
	for(int i=0;i<numberOfFrames;i++){
		frametable[i] = (int*)malloc(4*sizeof(int));
		for(int j=0;j<4;j++) frametable[i][j] = 0;
	} 
}

bool FrametableRANDOM::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){
	for(int i=0;i<numberOfFrames;i++) if(frametable[i][0] == pagenumber && frametable[i][1] == processnumber){
		if(printcheck>0) cout<<"The process number "<<processnumber<<" has a hit at frame "<<i<<" at run time "<<runtime<<endl;
		return false;
	} 
	if(printcheck>0) cout<<"The process number "<<processnumber<<" has a fault at "<<runtime<<endl;
	processes[processnumber-1].faultcount++;
	// cout<<"Here"<<endl;
	return true;
}

void FrametableRANDOM::pageReplacement(vector<Process>& processes,int pagenumber, int processnumber, int currenttime, Random* random){
	for(int i=numberOfFrames-1;i>=0;i--){
		if((frametable[i][0]==0)&&(frametable[i][1]==0)){
			frametable[i][0] = pagenumber;
			frametable[i][1] = processnumber;
			frametable[i][2] = currenttime;
			return;
		}
	}
	int randomNumber = random->get();
	int evictedframe = randomNumber%numberOfFrames;
	int evictedprocess = frametable[evictedframe][1];
	int evictedprocTime = frametable[evictedframe][2];
	processes[evictedprocess-1].residencytime += currenttime - evictedprocTime;
	processes[evictedprocess-1].evictioncount++;
	frametable[evictedframe][0] = pagenumber;
	frametable[evictedframe][1] = processnumber;
	frametable[evictedframe][2] = currenttime;
}
#include "FrametableFIFO.h"
#include <iostream>
#include <string>
FrametableFIFO::FrametableFIFO(char* argv[]){
	numberOfFrames = stoi(string(argv[1]))/stoi(string(argv[2]));
	printcheck = stoi(string(argv[7]));
}

bool FrametableFIFO::pageFaultCheck(vector<Process>& processes, int pagenumber, int processnumber, int runtime){
	for(int i=0;i<frametable.size();i++) if(frametable[i][0] == pagenumber && frametable[i][1] == processnumber){
		if(printcheck>0) cout<<"The process number "<<processnumber<<" has a hit at frame "<<i<<" at run time "<<runtime<<endl;
		return false;
	} 
	if(printcheck>0) cout<<"The process number "<<processnumber<<" has a fault at "<<runtime<<endl;
	processes[processnumber-1].faultcount++;
	// cout<<"Here"<<endl;
	return true;
}

void FrametableFIFO::pageReplacement(vector<Process>& processes,int pagenumber, int processnumber, int currenttime, Random* random){
	if(numberOfFrames == frametable.size()){
		vector<int> buf(frametable[0]);
		processes[buf[1]-1].residencytime += currenttime - buf[2];
		processes[buf[1]-1].evictioncount++;
		frametable.pop_front();
	}
	frametable.push_back(vector<int>{pagenumber,processnumber,currenttime});
}
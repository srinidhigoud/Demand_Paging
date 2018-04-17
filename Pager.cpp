#include "Pager.h"
#include <queue>
#include <iostream>
Pager::Pager(char* argv[], Frametable * frametable, Random* rand){
	this->random = rand;
	this->frametable = frametable;
	machineSize = stoi(string(argv[1]));
	pageSize = stoi(string(argv[2]));
	processSize = stoi(string(argv[3]));
	jobMix = stoi(string(argv[4]));
	referenceNumber = stoi(string(argv[5]));
	algorithm = string(argv[6]);
	printcheck = stoi(string(argv[7]));
}

void Pager::run(){
	if(jobMix == 1) {
		processes.push_back(Process(processSize, 1, referenceNumber));
		for(int runtime=1;runtime<=referenceNumber;runtime++){
			
			int pagenumber = processes[0].getnextWord()/pageSize;
			if(frametable->pageFaultCheck(processes, pagenumber,1, runtime)) frametable->pageReplacement(processes, pagenumber, 1, runtime, random);
			processes[0].nextreference(1,0,0,random);
		}
	}
	else if(jobMix==2 || jobMix==3 || jobMix==4 ){
		queue<int> roundrobin;
		for(int i=0;i<4;i++){
			processes.push_back(Process(processSize,i+1,referenceNumber));
			roundrobin.push(i);	
		} 
		double A[4];
		double B[4];
		double C[4];
		if(jobMix == 2){
			for(int i=0;i<4;i++){
				A[i] = 1;
				B[i] = 0;
				C[i] = 0;
			}
		}
		else if(jobMix == 3){		
			for(int i=0;i<4;i++){
				A[i] = 0;
				B[i] = 0;
				C[i] = 0;
			}	
		}
		else if(jobMix == 4){
			A[0] = 0.75;	B[0] = 0.25;	C[0] = 0;
			A[1] = 0.75;	B[1] = 0;       C[1] = 0.25;
			A[2] = 0.75;	B[2] = 0.125;	C[2] = 0.125;
			A[3] = 0.5;  	B[3] = 0.125;	C[3] = 0.125;
		}
		int runtime = 0;
		while(!roundrobin.empty()){
			int proc_number = roundrobin.front()+1;
			if(processes[proc_number-1].hasended()) roundrobin.pop();
			else if(processes[proc_number-1].hasfinishedquantum()){
				roundrobin.pop();
				roundrobin.push(proc_number-1);
			}
			else{
				runtime++;
				int pagenumber = processes[proc_number-1].getnextWord() / pageSize;
				if(frametable->pageFaultCheck(processes, pagenumber,proc_number, runtime)) frametable->pageReplacement(processes, pagenumber, proc_number, runtime, random);
				else {
				} 
				processes[proc_number - 1].nextreference(A[proc_number-1], B[proc_number-1], C[proc_number-1], random);
			}
		}
		
	}
}

void Pager::print(){
	int totalpagefaults = 0;
	int totalresidencytime = 0;
	int totalevictiontimes = 0;
	cout<<endl;
	printf("The machine size is %d\n",machineSize);
	printf("The page size is %d\n", pageSize);
	printf("The process size is %d\n", processSize);
	printf("The job mix number is %d\n", jobMix);
	printf("The number of references per process is %d\n", referenceNumber);
	cout<<"The replacement algorithm is "<<algorithm<<endl;
	printf("The level of debugging is %d\n",printcheck);
	cout<<endl;
	for(int processnumber = 0; processnumber<processes.size();processnumber++){
			totalevictiontimes += processes[processnumber].evictioncount;
			totalresidencytime += processes[processnumber].residencytime;
			totalpagefaults += processes[processnumber].faultcount;
			cout<<"Process "<<processnumber+1<<" had "<<processes[processnumber].faultcount<<" faults and ";
			if(processes[processnumber].evictioncount>0)cout<<(double)processes[processnumber].residencytime/processes[processnumber].evictioncount<<" average residency."<<endl;
			else cout<<endl<<"\t"<<"With no evictions, the average residence is undefined."<<endl;
			
	}

	cout<<endl;
	cout<<"The total number of page faults is "<<totalpagefaults;
	if(totalevictiontimes>0)cout<<" and the overall average residency is "<<(double)totalresidencytime/totalevictiontimes<<"."<<endl;
	else cout<<endl<<"\t"<<"With no evictions, the average residence is undefined."<<endl;
	cout<<endl;
}


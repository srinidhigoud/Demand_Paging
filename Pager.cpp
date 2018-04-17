#include "Pager.h"
#include <queue>
#include <iostream>
Pager::Pager(char* argv[], Frametable * frametable, Random* rand){//Constructor
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

void Pager::run(){//call this function to execute the pager
	if(jobMix == 1) {//for the case when job mix is 1, simplest case, consecutive
		processes.push_back(Process(processSize, 1, referenceNumber));
		for(int runtime=1;runtime<=referenceNumber;runtime++){
			
			int pagenumber = processes[0].getnextWord()/pageSize;
			if(frametable->pageFaultCheck(processes, pagenumber,1, runtime)) frametable->pageReplacement(processes, pagenumber, 1, runtime, random);
			processes[0].nextreference(1,0,0,random);
		}
	}
	else if(jobMix==2 || jobMix==3 || jobMix==4 ){//for cases when job mix is not 1
		queue<int> roundrobin;//create a queue for round robin scheduling
		for(int i=0;i<4;i++){
			processes.push_back(Process(processSize,i+1,referenceNumber));//push 4 pricesses into the vector
			roundrobin.push(i);	//for scheduling
		} 
		//allocate A,B,C values 
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
		int runtime = 0;//initiate the run time
		while(!roundrobin.empty()){//while there are processes that still have references left 
			int proc_number = roundrobin.front()+1;
			if(processes[proc_number-1].hasended()) roundrobin.pop();//if process's reference size has reduced remove the process 
			else if(processes[proc_number-1].hasfinishedquantum()){//if the process completed its quantum put it at the back, otherwise reduce its quantum and reference count size
				roundrobin.pop();
				roundrobin.push(proc_number-1);
			}
			else{
				//otherwose increase runtime
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
//Print the entire allocated data
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


#include "Process.h"
#include <climits>
Process::Process(int processSize, int processnumber, int referenceSize){//Constructor
	residencytime = 0;
	evictioncount = 0;
	faultcount = 0;
	quantum = 3;
	this->referenceSize = referenceSize;
	nextWord = (111 * processnumber) % processSize;//initialization
	this->processSize = processSize;
}

void Process::nextreference(double A, double B, double C, Random* rand){//Prepare the next reference beforehand for easy access of next word
	int random = rand->get();
	double quotient = random / (INT_MAX + 1.0);
	if (quotient < A) nextWord = (nextWord + 1) % processSize;
	else if (quotient < A + B) nextWord = (nextWord - 5 + processSize) % processSize;
	else if (quotient < A + B + C) nextWord = (nextWord + 4) % processSize;
	else {
		int randomRef = rand->get() % processSize;
		nextWord = randomRef;
	}
}

int Process::getnextWord(){//Return the next word
	return nextWord;
}

bool Process::hasended(){//If the reference times of this process has ended return true
	if(referenceSize==0) return true;
	else return false;
}

bool Process::hasfinishedquantum(){//If the quantum of this process is ended reset and return true, otherwise reduce quantum, reference size and return false
	if(quantum==0){
		quantum = 3;
		return true;
	} 
	else{
		quantum--;
		referenceSize--;
		return false;
	} 
}
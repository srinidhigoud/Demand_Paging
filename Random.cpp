#include "Random.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
Random::Random(char* argv[]){
		k=0;
		filename = "Random_Number.txt";
		printcheck = (stoi(string(argv[7]))>1)?true:false;//condition if this random needs to be printed or not
	}

void Random::reset(){
		this->k = 0;//reset the value
	}

int Random::get(){
		int n = 0;
		ifstream source;
		source.open(filename);
		string line;
		int i=0;
		while(getline(source, line)){//iterate to the present count in the text file and retrieve the random number
			if(i==k){
				istringstream iss(line);
				iss>>n;
				break;
			}
			else {
				istringstream iss(line);
				iss>>n;
				i++;
			}
		}
		k++;//keep incrementing the present count so as to point to the next random number for next access
		source.close();
		if(printcheck) cout<<n<<endl;
		return n;
	}
#include "Random.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
Random::Random(char* argv[]){
		k=0;
		filename = "Random_Number.txt";
		printcheck = (stoi(string(argv[7]))>1)?true:false;
	}

void Random::reset(){
		this->k = 0;
	}

int Random::get(){
		int n = 0;
		ifstream source;
		source.open(filename);
		string line;
		int i=0;
		while(getline(source, line)){
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
		k++;
		source.close();
		if(printcheck) cout<<n<<endl;
		return n;
	}
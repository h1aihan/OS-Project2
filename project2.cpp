#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <typeinfo>
#include <iterator>
#include <stdlib.h>
#include <queue>
using namespace std;

//process class
class Process{
public:
	Process(){};
	Process(vector<string> v){
		id = v[0];
		frame = atoi(v[1].c_str());
		for(unsigned int i=2; i<v.size(); ++i){
			string token;
			size_t j = 0;
			while((j = v[i].find("/")) != std::string::npos){
				token = v[i].substr(0, j);
				v[i].erase(0, j+1);
				arrive.push_back(atoi(token.c_str()));
			}
			remove.push_back(atoi(v[i].c_str()));
		}
	}
	string id;
	int frame;
	vector<int> arrive;
	vector<int> remove;
};

//parse the input file to a class
Process parse(string a){
	vector<string> temp;
	string token;
	int count=0;
	size_t i = 0;
	while((i = a.find(" ")) != std::string::npos){
		token = a.substr(0, i);
		//cout << token << endl;
		a.erase(0, i+1);
		temp.push_back(token);
	}
	temp.push_back(a);
	Process pro(temp);
	return pro;
}

void next_fit(vector<Process> p){
	cout << "time 0ms: Simulator started (Contiguous -- Next-Fit)" <<endl;
	int count = -1;
	while(1){
		count++;
		//check removal and arrival 
		for(unsigned int i=0; i<p.size(); i++){
			if(p[i].remove[0] == count){
				cout << "time "<<count << "ms: Process "<<p[i].id<<" removed:" << endl; 
			}
			if(p[i].arrive[0] == count){
				cout << "time "<<count<<"ms: Process "<< p[i].id<<" arrived (requires "<<p[i].frame<<" frames)" << endl;
			}
		}
	}
}

int main(int argc, char* argv[]){
	if(argc != 2){
    	std::cerr << "The number of arguments entered are wrong!";
    	return 1;
  	}

	ifstream in_str(argv[1]);
	if (!in_str.good()){
		// check if the file can be read
		cerr << "Can't open " << argv[1] << " to read.\n"; 
		return EXIT_FAILURE;
	}

	string a;
	vector<Process> process;
	while(getline(in_str, a)){
		process.push_back(parse(a));
	}

	next_fit(process);


}
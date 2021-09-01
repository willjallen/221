#include <fstream>
#include <iostream>

using namespace std;

int main(){
	ifstream infile; 
	infile.open("input.txt", ios_base::in); 

 	if (infile.fail())
	{
		cout << "The File was not successfully open." << endl;
		exit(1); // ends ENTIRE program!!!
	}

	cout << "Reading from the file" << endl; 
	
	int data;

	while(infile >> data){
		cout << data << endl;
		cout << endl;
	}

	return 0;
}
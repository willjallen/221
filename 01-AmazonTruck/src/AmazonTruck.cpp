#include <string>

#include "AmazonTruck.h"
#include "Package.h"


bool AmazonTruck::isFull(){
	return false;
}


void AmazonTruck::makeEmpty(){
	this->truck->clear();
}


unsigned short AmazonTruck::totalVolumnSoFar(){
	return 0;
}


void AmazonTruck::fillFromFile(string filename){
	ifstream infile; 
	infile.open("input.txt", ios_base::in); 

 	if (infile.fail())
	{
		cout << "The File was not successfully open." << endl;
		exit(1); 
	}

	cout << "Reading from the file" << endl; 

	string address1;
	string city;
	string state;
	int zip;

	unsigned short int width;
	unsigned short int height;
	unsigned short int depth;

	string ID;
	float weight;

	string liquidType;
	bool flammable;

	




	
}

Package AmazonTruck::displayLastItenInTruck(){
	return nullptr;
}




	
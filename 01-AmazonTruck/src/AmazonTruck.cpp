#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "AmazonTruck.h"
#include "Package.h"


bool AmazonTruck::isFull(){
	return totalVolumnSoFar() > volumn;
}


void AmazonTruck::makeEmpty(){
	truck->clear();
}


unsigned short AmazonTruck::totalVolumnSoFar(){

	unsigned short totalVolume = 0;

	for(auto package = truck->begin(); package != truck->end(); ++package){
		totalVolume += (*package).getVolume();
	}

	return totalVolume;
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

	string cargoType;
	bool isLiquid;
	string liquidType;
	bool flammable;


	string line;
	const int ITEMS_IN_ROW = 11;
	int colIndex = 0;

	while(getline(infile, line)){

		std::stringstream linestream(line);
    	std::string cell;


    	while(getline(linestream, cell, ',')){

    		/*
    		"And packages with negatives in either width, height, or depth, 
    		should be ignored and not placed in the truck."
    		*/
    		switch(colIndex){
    			// address1
    			case(0): 
    				address1 = cell;
    				break;
    			case(1):
    				city = cell;
    				break;
    			case(2):
    				state = cell;
    				break;
    			case(3):
    				zip = stoi(cell);
    				break;
    			case(4):
    				width = ((unsigned short)stoi(cell));
    				// Check for negative values

    				break;
    			case(5):
    				height = ((unsigned short)stoi(cell));
    				// Check for negative values

    				break;
				case(6):
    				depth = ((unsigned short)stoi(cell));
    				// Check for negative values

    				break;
    			case(7):
    				ID = cell;
    				break;
    			case(8):
    				weight = stof(cell);
    				break;
    			case(9):
    				cargoType = cell;
    				break;
    			case(10):
    				flammable = stoi(cell);
    				break;
    		}

    		// Create the package		

    		if(colIndex >= ITEMS_IN_ROW){
    			// Error, more data types than truck can hold
    		}else{
    			++colIndex;
    		}

    	}

    	colIndex = 0;

    	// Check if there is space in the truck for more packages


	}





	
}

void AmazonTruck::displayLastItenInTruck(){
}




	
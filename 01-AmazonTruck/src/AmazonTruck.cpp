#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "AmazonTruck.h"
#include "Package.h"


bool AmazonTruck::isFull(){
	return totalVolumnSoFar() >= volumn;
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
		cout << "The file was not successfully opened." << endl;
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

    	bool invalidPackage = false;


    	while(getline(linestream, cell, ',')) {

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

    				if(width < 0){
    					invalidPackage = true;
    				}

    				break;
    			case(5):
    				height = ((unsigned short)stoi(cell));

    				if(height < 0){
    					invalidPackage = true;
    				}


    				break;
				case(6):
    				depth = ((unsigned short)stoi(cell));

    				if(depth < 0){
    					invalidPackage = true;
    				}


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

    		if(colIndex >= ITEMS_IN_ROW){
    			// Error, more data types than truck can hold
    		}else{
    			++colIndex;
    		}

    	}

    	unsigned short volume = width * height * depth;
    	Dimension dimension(width, height, depth);

    	// Check if there is space in the truck for more packages
    	bool noSpace = false;
    	if(totalVolumnSoFar() + volume > this->volmn){
    		noSpace = true;
    	}
		
		// Create the package
		if(!invalidPackage && !noSpace){
			Address address(address1, city, state, zip);
			Package package(address, dimension, ID, weight);
			package.setVolume(volume);

		}	

    	colIndex = 0;



	}





	
}

void AmazonTruck::displayLastItenInTruck(){
}




	
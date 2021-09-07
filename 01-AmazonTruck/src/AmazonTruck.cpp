#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "AmazonTruck.h"
#include "Package.h"
#include "Liquid.h"


/* 
 If your truck isn't full, you should add the package, even if its volume
 is more than the space left(This may or may not happen; it depends on the truck's volume). 
 Basically, You keep adding packages (non-negative ones) until there is 
 no (+ve) space left-- the truck is full. 
*/

// The volume overflow is simply melting into the fourth dimension
// Leave it to Jeff Bezos to reivent physics so he can ship more packages 
bool AmazonTruck::isFull(){
	if(volumn - totalVolumnSoFar() < 0){
    		return true;
    	}
    return false;
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
	infile.open(filename, ios_base::in); 

 	if (infile.fail())
	{
		cout << "The file was not successfully opened." << endl;
		exit(1); 
	}

	cout << "Reading from the file" << endl; 

	string address1 = "";
	string city = "";
	string state = "";
	int zip = 0;

	int width = 0;
	int height = 0;
	int depth = 0;

	string ID = "";
	float weight = 0.0;

	string cargoType = "";
	bool isLiquid = false;
	string liquidType = "";
	bool flammable = false;


	string line = "";
	const int ITEMS_IN_ROW = 11;
	int colIndex = 0;

	while(getline(infile, line)){

		std::stringstream linestream(line);
    	std::string cell = "";

    	bool invalidPackage = false;


    	while(getline(linestream, cell, ',')) {


    		/*
    		"And packages with negatives in either width, height, or depth, 
    		should be ignored and not placed in the truck."
    		*/
    		switch(colIndex){
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
    				width = stoi(cell);

    				if(width < 0){
    					invalidPackage = true;
    				}

    				break;
    			case(5):
    				height = stoi(cell);

    				if(height < 0){
    					invalidPackage = true;
    				}


    				break;
				case(6):
    				depth = stoi(cell);

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
    			invalidPackage = true;
    		}else{
    			++colIndex;
    		}

    	}

		// Create the package
		if(!invalidPackage && !isFull()){

	    	unsigned short volume = width * height * depth;
	    	Dimension dimension(width, height, depth);
			Address address(address1, city, state, zip);

			Package item;

			// Check if liquid
			if(cargoType.find("cargo") == string::npos){
				Liquid liquid(address, dimension, ID, weight, cargoType, flammable);
				item = liquid;			
			}else{

				Package package(address, dimension, ID, weight);
				item = package;
			}
			
			item.setVolume(volume);
			truck->push_back(item);

		}	

    	colIndex = 0;



	}





	
}

void AmazonTruck::displayLastItenInTruck(){
	cout << truck->back() << endl;
}




void AmazonTruck::displayAllItemsInTruck(){
	for(auto package = truck->begin(); package != truck->end(); ++package){
		cout << (*package) << endl;
	}
}
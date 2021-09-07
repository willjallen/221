//============================================================================
// Name        : Amazon.cpp
// Author      : Prof. Lupoli
// Version     :
// Copyright   : Your copyright notice
// Description : Project 0, filling an Amazon Truck
//============================================================================

#include <iostream>
using namespace std;

#include "AmazonTruck.h"
#include "Liquid.h"
#include "Address.h"
#include "Dimension.h"

int main()
{

	/*   All test code */
	Address testAddress("1600 Penn. Ave.", "DC", "DC", 00125);
	Dimension testDimension(12, 6, 12);
	Liquid testLiquid(testAddress, testDimension, "HJGASDHG12765T", 12.3, "cleaner", true);
	testLiquid.setVolume(12 * 6 * 12);

	cout << "Test address cout overload: " << endl;
	cout << testAddress << endl;

	cout << "Test dimension cout overload: " << endl;
	cout << testDimension << endl;
	
	cout << "Test liquid cout overload: " << endl;
	cout << testLiquid << endl;
	

	AmazonTruck* fromCollegeStation = new AmazonTruck( (short int) 1664);
	fromCollegeStation->fillFromFile("../datafile.csv");

	cout << "Last item: " << endl;
	fromCollegeStation->displayLastItenInTruck();

	// cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	// cout << testAddress << endl;

	// fromCollegeStation->displayAllItemsInTruck();


	int hold = 0;
	cin >> hold;
	return 0;
}

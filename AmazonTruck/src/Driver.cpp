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

	AmazonTruck* fromCollegeStation = new AmazonTruck( (short int) 1664);
	//fromCollegeStation->fillFromFile("data.txt");


	fromCollegeStation->displayLastItenInTruck();

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << testAddress << endl;
	int hold = 0;
	cin >> hold;
	return 0;
}

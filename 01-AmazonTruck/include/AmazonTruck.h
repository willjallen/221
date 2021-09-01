/*
 * AmazonTruck.h
 *
 *  Created on: Jan 9, 2020
 *      Author: Prof. Lupoli
 */

#ifndef AMAZONTRUCK_H_
#define AMAZONTRUCK_H_

#include <iostream>
#include <vector>
#include <ostream>
using namespace std;

#include "Package.h"

class AmazonTruck {
public:
	AmazonTruck(short v) {volumn = v; }
	~AmazonTruck() { delete truck; }

	bool isFull();
	void makeEmpty(); // just empty the truck of items
	unsigned short totalVolumnSoFar();

	/*
	 * 1. How will you parse the address from the data file to match address, town, etc...?
	 */
	void fillFromFile(string filename);
	void displayLastItenInTruck();



private:

	/*
	 * No other data members are allowed!!!
	 */
	vector <Package> *truck = new vector <Package>;
	unsigned short volumn;
	/*
	 * No other data members are allowed!!!
	 */

};

#endif /* AMAZONTRUCK_H_ */

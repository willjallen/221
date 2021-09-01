/*
 * Address.h
 *
 *  Created on: Jan 10, 2020
 *      Author: Prof. Lupoli
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <iostream>
using namespace std;

class Address {
public:
	Address();
	Address(string a1, string c, string st, int z);

	const string& getAddress1() const { return address1; }
	void setAddress1(const string& address1) { this->address1 = address1; }

	const string& getCity() const { return city; }
	void setCity(const string& city) { this->city = city; }

	const string& getState() const { return state; }
	void setState(const string& state) { this->state = state; }

	int getZip() const { return zip; }
	void setZip(int zip) { this->zip = zip; }



	// overloaded cout
	// overloaded equal
	const Address &operator = (const Address &source);


private:
	string address1;
	string city;
	string state;
	int zip;


};

inline Address::Address(string a1, string c, string st, int z)
{
	this->address1 = a1;
	this->city = c;
	this->state = st;
	this->zip = z;

}

inline Address::Address() { }

inline const Address & Address::operator = (const Address &source)
{
	if(this == &source) // this is a self assignment checker
	{ return *this; }	// returns the pointer to the current object
	// otherwise copy

	//new-instance now = source instance
	this->address1 = source.address1;
	this->city = source.city;
	this->state = source.state;
	this->zip = source.zip;

	return *this; // returns previously empty instance
}

inline ostream& operator<< (ostream& os, const Address& address){
	os << "Address1":  << address.getAddress1() << endl;
	os << "City: " << address.getCity() << endl;
	os << "State: " << address.getState() << endl;
	os << "Zip: " << address.getZip() << endl;
	return os;
} 

#endif /* ADDRESS_H_ */




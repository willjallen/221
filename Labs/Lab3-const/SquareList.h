///////////////////////////////////////////////////////////////
//  File:   SquareList.h
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: 
//  Date:   9/6/2019
//  Usage:  Complete definition of Class SquareList.h
///////////////////////////////////////////////////////////////
#ifndef SQUARELIST_H
#define SQUARELIST_H

#include <list>
#include <cmath>
#include "InnerSquareList.h"

class SquareList
{
	//the horizonal list containing all inner lists
	std::list<InnerSquareList> inners;
public:
	SquareList();
	~SquareList();

	//Keep the length of each inner list satisfying the definition of a Square List
	void consolidate();

	//insert 
	void addFirst(const int data);

	void addLast(const int data);

	int removeFirst();

	//insert a value to be at location "pos"
	void add(int pos, const int data);

	int remove(int pos);

	int get(int pos) const;

	void set(int pos, const int data);

	//total number of nodes in all inner lists
	int size() const; // here

	//Position of first occurence of a value
	int indexOf(const int data) const; //here

	//Printing out information of Square List for debugging
	void dump() const; //here
};

#endif
///////////////////////////////////////////////////////////////
//  File:   InnerSuqareList.h
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: 
//  Date:   9/6/2019
//  Usage:  Complete definition of Class InnerSquareList.h
///////////////////////////////////////////////////////////////
#ifndef INNERSQUARELIST_H
#define INNERSQUARELIST_H

#define INTNULL -1

#include <iostream>

// Node used in the SquareList
typedef struct tagNode
{
	int value;
	struct tagNode* next;
}Node;

class InnerSquareList
{
	//pointer to the first Node in the inner list
	Node* m_header;

	//pointer to the last node in the inner list
	Node* m_tail;

	//number of the nodes
	size_t m_length;

public:
	InnerSquareList();

	//initialize an inner list with given data
	InnerSquareList(Node* const header, Node* const tail, const size_t length);
	
	~InnerSquareList();

	//delete all dynamically allocated nodes
	void clean();

	Node* getHeader() const; //here

	Node* getTail() const; //here

	//data should be at position "pos" after insertion
	void add(const int pos, const int data);

	//push_front of STL
	void addFirst(const int data);

	//insert as the last element
	void addLast(const int data);

	//remove node, position starts from 0
	int remove(const int pos);

	//return the element at position pos
	int get(const int pos) const; //here

	//change the value at position pos to data
	void set(const int pos, const int data);

	//total number of nodes in the inner list
	size_t size() const; //here

	//find the index of given data, return -1 if not found
	int indexOf(const int data) const; //here

	//merge another inner list to rear of current inner list
	//the second inner list should be empty after merge
	void merge(InnerSquareList &isl); //not

	//split an inner list at mid point, return the second half
	//the first half should be the same, or one element less thant the second half
	InnerSquareList split();

	//print of all node values and the last node in O(1)
	//check the sample output for format
	void dump() const; //here
};

#endif
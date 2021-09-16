/**********************************************
 ** File : Driver.cpp
 ** Project : CSCE 121 Project 2, Spring 2019
 ** Author : William Allen
 ** Date : 9/16/21
 ** Section : ???
 ** E-mail : willallen@tamu.edu
 **
 ** This file contains the main driver for Project 2.
 ** The following program is used to test the correctness 
 ** and completeness of the Circular Linked List.
 ** 
 **********************************************/

#include "bufferlist.h"
BufferList::BufferList(int minBufCapacity){
    // **************************************
    // Implement the alternative constructor
    // **************************************
}
BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    // *****************************
    // Implement clear() function
    // *****************************
}

void BufferList::enqueue(const int& data) {
    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************
}

int BufferList::dequeue() {
    // *****************************
    // Implement dequeue() function
    // *****************************
}

BufferList::BufferList(const BufferList & rhs){
    // *******************************
    // Implement the copy constructor
    // *******************************
}

const BufferList & BufferList::operator=(const BufferList & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
    return *this;
}

void BufferList::dump(){
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}
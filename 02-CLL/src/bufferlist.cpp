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

#include "../include/bufferlist.h"
BufferList::BufferList(int minBufCapacity){
    // **************************************
    // Implement the alternative constructor
    // **************************************

    if(minBufCapacity < 1){
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
    }else{
        m_minBufCapacity = minBufCapacity;
    }


    // Create new buffer
    m_cursor = new Buffer(m_minBufCapacity);

    // Set the buffer's m_next to itself
    m_cursor->m_next = m_cursor;

    m_listSize = 1;


}
BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    // *****************************
    // Implement clear() function
    // *****************************

    Buffer* currBuffer = m_cursor;

    for(int i = 0; i < m_listSize; i++){
        Buffer* nextBuffer = currBuffer->m_next;
        delete currBuffer;
        currBuffer = nextBuffer;

    }

    m_listSize = 0;




}

void BufferList::enqueue(const int& data) {
    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************


    try{
        m_cursor->enqueue(data);
    }catch(std::overflow_error &e){
        // std::cout << "overflow here" << std::endl;
        // dump();
        // std::cout << std::endl;
        // std::cout << std::endl;
        // // Buffer at m_cursor is full, create new buffer
        // std::cout << m_cursor << std::endl;
        createNewBuffer(m_cursor);
        // std::cout << "made new buffer" << std::endl;
        // std::cout << m_cursor << std::endl;
        // m_cursor->dump();
        m_cursor->enqueue(data);
        // std::cout << "enqueued" << std::endl;
        // m_cursor->dump();
        // std::cout << std::endl;


    }

}

int BufferList::dequeue() {
    // *****************************
    // Implement dequeue() function
    // *****************************

    bool success = false;
    bool exception = false;

    int data = 0;

    while(!success){
        exception = false;

        if(m_cursor == getOldestBuffer()){
            if(m_cursor->count() == 0){
                throw std::underflow_error("BufferList underflow");
                return -1;
            }
        }

        try{
            data = getOldestBuffer()->dequeue();
        }catch(std::underflow_error &e){
            exception = true;
            deleteOldestBuffer();
        }

        if(!exception) success = true;
    }

    return data;


}

BufferList::BufferList(const BufferList & rhs){
    // *******************************
    // Implement the copy constructor
    // *******************************

    // Copy member variables
    m_listSize = rhs.m_listSize;
    m_minBufCapacity = rhs.m_minBufCapacity;

    m_cursor = nullptr;

    // Deep copy linked list

    // Get oldest buffer
    Buffer* rhsBuffer = rhs.getOldestBuffer();

    // Store one iteration behind to do linking
    Buffer* prevNewBuffer = nullptr;
    Buffer* newBuffer = nullptr;
    Buffer* firstBuffer = nullptr;

    for(int i = 0; i < m_listSize; i++){
        newBuffer = new Buffer(*rhsBuffer);
        if(i == 0) firstBuffer = newBuffer;

        rhsBuffer = rhsBuffer->m_next;

        if(prevNewBuffer != nullptr){
            prevNewBuffer->m_next = newBuffer;
        }

        prevNewBuffer = newBuffer;
        
    }

    m_cursor = newBuffer;
    m_cursor->m_next = firstBuffer;



}


const BufferList & BufferList::operator=(const BufferList & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
    if(this == &rhs){
        // Self assignment 
        return *this;
    }

    if(m_listSize != 0){
        clear();
    }


    *this = BufferList(rhs);

    return *this;
}

void BufferList::createNewBuffer(Buffer* prevBuffer){

    /*
        The size of a new buffer is a factor of the size of the previous buffer.
        The maximum size of a buffer cannot exceed MAX_FACTOR * m_minBufCapacity.
        If it does, the buffer will be created with capacity of m_minBufCapacity.

    */

    Buffer* newBuffer = nullptr;

    if(prevBuffer->m_capacity * INCREASE_FACTOR > m_minBufCapacity * MAX_FACTOR){
        newBuffer = new Buffer(m_minBufCapacity);
    }else{
        newBuffer = new Buffer(prevBuffer->m_capacity * INCREASE_FACTOR);
    }

    // Update the circular linked list 

    // The previous last buffer would point to the oldest buffer (the one in the 'first' position)
    newBuffer->m_next = prevBuffer->m_next;
    prevBuffer->m_next = newBuffer;


    // Set the cursor to the new buffer
    m_cursor = newBuffer;

    m_listSize += 1;

    // b1 
    // - m_next = b1

    // b1 
    // - m_next = b2
    // b2 
    // - m_next = b1

    // b1 - m_next = b2
    // b2 - m_next = b3
    // b3 - m_next = b1



}


void BufferList::deleteOldestBuffer(){

    // Store the oldest buffer's m_next
    Buffer* oldestBuffer = getOldestBuffer();
    Buffer* tempNext = oldestBuffer->m_next;

    // Delete the buffer
    delete oldestBuffer;

    // The youngest buffer(m_cursor)'s m_next is now the buffer after the oldest buffer
    m_cursor->m_next = tempNext;

    m_listSize -= 1;

}


// This function exists for clarity
Buffer* BufferList::getOldestBuffer() const {
    // The oldest buffer will always been m_cursor->m_next (the buffer at position 1)
    
    return m_cursor->m_next;

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
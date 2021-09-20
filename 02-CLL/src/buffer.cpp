/**********************************************
 ** File : Driver.cpp
 ** Project : CSCE 121 Project 2, Spring 2019
 ** Author : William Allen
 ** Date : 9/16/21
 ** Section : ???
 ** E-mail : willallen@tamu.edu
 **
 ** This file contains the Circular Linked List Buffer Implemenation.
 ** 
 **********************************************/

#include <stdexcept>
#include "../include/buffer.h"



Buffer::Buffer(int capacity){
    
    if(capacity > 1){
        m_capacity = capacity;

        m_buffer = new int[m_capacity]();
        m_count = 0;
        m_start = 0;
        m_end = 0;

    }else{
        m_capacity = 0;
        m_buffer = nullptr;
        m_count = 0;
        m_start = 0;
        m_end = 0;

    }

}

void Buffer::clear(){

    delete[] m_buffer;

    m_buffer = nullptr;
    m_count = 0;
    m_start = 0;
    m_end = 0;

}

Buffer::~Buffer(){
    clear();
}

int Buffer::count() {return m_count;}

int Buffer::capacity() const {return m_capacity;}

bool Buffer::full() {
    return m_count >= m_capacity;
}

bool Buffer::empty() {
    return m_count == 0;

}

void Buffer::enqueue(int data){
    // Check if out of room
    if(m_count >= m_capacity){
        throw std::overflow_error("Overflow");
    }else{
        m_buffer[m_end] = data;
        m_end = nextIndex(m_end);
        m_count += 1;
    }

}

int Buffer::dequeue(){
    int data = 0;

    // Check if array is empty
    if(m_count <= 0){
        throw std::underflow_error("Underflow");
    }else{
        data = m_buffer[m_start];
        m_start = nextIndex(m_start);
        m_count -= 1;
    }

    return data;
}

int Buffer::nextIndex(int currIndex) {
    if(currIndex == m_capacity-1){
        // If at the end of the array
        // The next index is at the beginning
        return 0;
    }else{
        return ++currIndex;
    }
}

int Buffer::previousIndex(int currIndex) {
    if(currIndex == 0){
        // If at the beginning of the array
        // The next index is at the end
        return m_capacity-1;
    }else{
        return --currIndex;
    }
}




Buffer::Buffer(const Buffer & rhs){

    // Deep copy
    // Create new memory and copy rhs

    if(rhs.m_capacity > 1){
        m_capacity = rhs.m_capacity;

        m_buffer = new int[m_capacity]();

        m_count = rhs.m_count;
        m_start = rhs.m_start;
        m_end = rhs.m_end;

        // Fill the array with a copy
        for(int i = 0; i < m_capacity; ++i){
            m_buffer[i] = rhs.m_buffer[i];
        }

    }else{
        m_capacity = 0;

        m_buffer = nullptr;
        m_count = 0;
        m_start = 0;
        m_end = 0;

    }
}

const Buffer & Buffer::operator=(const Buffer & rhs){

    if(this == &rhs){
        // Self assignment 
        return *this;
    }

    if(m_capacity != 0){
        delete[] m_buffer;
    }


    *this = Buffer(rhs);

    return *this;
}

void Buffer::dump(){
    int start = m_start;
    // int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}

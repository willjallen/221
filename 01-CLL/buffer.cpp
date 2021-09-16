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

#include "buffer.h"
#include <stdexcept>



Buffer::Buffer(int capacity){

    // **************************************
    // Implement the alternative constructor
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // **************************************
    
    if(capacity < 1){
        m_capacity = 0;
    }

    if(m_capacity != 0){
        m_capacity = capacity;

        m_buffer = new int[m_capacity];
        m_count = 0;
        m_start = m_buffer;
        m_end = m_buffer[m_capacity-1];

    }else{
        m_buffer = nullptr;
        m_count = 0;
        m_start = nullptr;
        m_end = nullptr;

    }

}

void Buffer::clear(){
    // ***********************************
    // Implement clear() function
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // ***********************************
}

Buffer::~Buffer(){
    clear();
}

int Buffer::count() const {return m_count;}

int Buffer::capacity() const {return m_capacity;}

bool Buffer::full() const {
    // **************************
    // Implement full() function
    // **************************
    return m_count >= m_capacity;
}

bool Buffer::empty(){
    // **************************
    // Implement empty() function
    // **************************

    delete m_buffer[m_capacity];

    m_buffer = nullptr;
    m_count = 0;
    m_start = nullptr;
    m_end = nullptr;

}

void Buffer::enqueue(int data){
    // ********************************
    // Implement enqueue(...) function
    // ********************************

    // Check if out of room
    if(count == m_capacity){
        throw std::overflow_error();
    }else{
        m_buffer[m_end] = data;
        m_end = nextIndex(m_end);
    }

}

int Buffer::dequeue(){
    // *****************************
    // Implement dequeue() function
    // *****************************

    // Check if array is empty
    if(count <= 0){
        throw std::underflow_error();
    }else{
        m_buffer[m_start] = data;
        m_start = previousIndex(m_start);
    }
}

int Buffer::nextIndex(int currIndex) const {
    if(currIndex == m_capacity-1){
        // If at the end of the array
        // The next index is at the beginning
        return 0
    }else{
        return ++currIndex;
    }
}

int Buffer::previousIndex(int currIndex) const {
    if(currIndex == 0){
        // If at the beginning of the array
        // The next index is at the end
        return m_capacity-1
    }else{
        return --currIndex;
    }
}

// cap = 6
// count = 0
// * = start
// $ = end


// [0$,0, 0, 0, 0, 0*]

// -> push [0]

// [0, 0$, 0, 0, 0, 0*]
// count = 1

// -> push [1]

// [0, 1, 0$, 0, 0, 0*]
// count = 2

// -> push [2]

// [0, 1, 2, 0$, 0, 0*]
// count = 3

// -> push [3]

// [0,1, 2, 3, 0$, 0*]
// count = 4

// -> push [4]

// [0, 1, 2, 3, 4, 0$*]
// count = 5

// -> push [5]

// [0$, 1, 2, 3, 4, 5*]
// count = 6

// -> pop

// [0$, 1, 2, 3, 4*, 5]
// count = 5
// -> 5

// -> pop

// [0$, 1, 2, 3*, 4, 5]
// count = 4
// -> 4

// -> pop

// [0$, 1, 2*, 3, 4, 5]
// count = 3
// -> 3

// -> pop

// [0$, 1*, 2, 3, 4, 5]
// count = 2
// -> 2

// -> pop

// [0$*, 1, 2, 3, 4, 5]
// count = 1
// -> 1

// -> pop

// [0$, 1, 2, 3, 4, 5*]
// count = 0
// -> 0




Buffer::Buffer(const Buffer & rhs){

    // Deep copy
    // Create new memory and copy rhs

    if(m_capacity > 1){
        m_capacity = capacity;

        m_buffer = new int[m_capacity];
        m_count = 0;
        m_start = m_buffer;
        m_end = m_buffer[m_capacity-1];

        // Fill the array with a copy

    }else{
        m_capacity = 0;

        m_buffer = nullptr;
        m_count = 0;
        m_start = nullptr;
        m_end = nullptr;

    }
}

const Buffer & Buffer::operator=(const Buffer & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
    return *this;
}

void Buffer::dump(){
    int start = m_start;
    int end = m_end;
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
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


#include <stdexcept>
#include "../include/bufferlist.h"
#include "../include/buffer.h"

class Tester{
    public:
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
    bool BufferEnqueueFull(int size);
    bool BufferCopyConstructor(const Buffer &buffer);
    void BufListEnqueuePerformance(int numTrials, int N);
};
int main(){
    Tester tester;
    int bufferSize = 10;
    Buffer buffer(bufferSize);
    {
        //testing insertion/removal for 1 data item
        cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
        if (tester.BufferEnqueueDequeue(buffer, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for half data size
        cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize/2))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for full data size
        cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion in a full buffer
        cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
        if (tester.BufferEnqueueFull(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing Buffer class copy constructor with buffer size less than zero
        cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
        Buffer buffer(-10);
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n"; 
    }
    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;//number of trials
        int N = 10000;//original input size
        tester.BufListEnqueuePerformance(M, N);
    }
    {
        //an example of BufferList::dump()
        cout << "\nHere is an example of a linked list:" << endl;
        BufferList bufferList(5);
        for (int i=40;i>0;i--)
            bufferList.enqueue(i);
        bufferList.dump();
    }
    return 0;
}

bool Tester::BufferEnqueueDequeue(Buffer &buffer, int dataCount){
    for (int i=0;i<dataCount;i++) {
        try{
            buffer.enqueue(i);
        }catch(const std::overflow_error &e){

             buffer.dump();
             std::cout << "----" << i << "------" << std::endl;
            return false;
        }  
    }

    for(int i=0;i<dataCount;i++){
        try{
            buffer.dequeue();
        }catch(const std::underflow_error &e){
             buffer.dump();
             std::cout << "----" << i << "------" << std::endl;
            return false;
        }  
    }



    return true;
}

bool Tester::BufferCopyConstructor(const Buffer &buffer){
    
    bool pass = true;

    Buffer newBuffer(buffer);

    if(newBuffer.capacity() != buffer.capacity()) pass = false;

    if(newBuffer.capacity() > 1){
        if(newBuffer.m_buffer == buffer.m_buffer) pass = false;
    }

    return pass;

}



bool Tester::BufferEnqueueFull(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++)
        aBuffer.enqueue(i);
    try{
        //trying to insert in a full buffer
        aBuffer.enqueue(size+1);
    }
    catch(overflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

void Tester::BufListEnqueuePerformance(int numTrials, int N){
    
}
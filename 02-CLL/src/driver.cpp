/**********************************************
 ** File : Driver.cpp
 ** Project : CSCE 221 Project 2, Fall 2021
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
#include <time.h>
#include <chrono>
#include "../include/bufferlist.h"
#include "../include/buffer.h"

class Tester{
    public:
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
    bool BufferEnqueueFull(int size);
    bool BufferCopyConstructor(const Buffer &buffer);

    bool BufferListEnqueueDequeue(BufferList& bufferList, int dataCount);
    bool BufferListDequeueEmpty(BufferList& bufferList);
    bool BufferListCopyConstructor(const BufferList &bufferlist);
    bool BufferListAssignmentConstructor(const BufferList &bufferlist);
    void BufListEnqueuePerformance(int numTrials, int N);

    // Custom test cases
    bool BufferListDequeueClearEmptyBuffer(BufferList &bufferlist);

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
        //testing insertion/removal for 1 data item
        cout << "\nTest case: BufferList class: Inserting/removing 1 items:\n";
        BufferList bufferList(0);
        if (tester.BufferListEnqueueDequeue(bufferList, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for 11 data items
        cout << "\nTest case: BufferList class: Inserting/removing 11 items:\n";
        BufferList bufferList(0);
        if (tester.BufferListEnqueueDequeue(bufferList, 11))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for 10000 data item
        cout << "\nTest case: BufferList class: Inserting/removing 10000 items:\n";
        BufferList bufferList(0);
        if (tester.BufferListEnqueueDequeue(bufferList, 10000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing removal of data item in empty bufferlist
        cout << "\nTest case: BufferList class: Dequeue empty list:\n";
        BufferList bufferList(0);
        if (tester.BufferListDequeueEmpty(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // BufferListAssignmentConstructor
        cout << "\nTest case: BufferList class: Assignment operator:\n";
        
        BufferList bufferList(5);
        for (int i=40;i>0;i--)
            bufferList.enqueue(i);

        if (tester.BufferListAssignmentConstructor(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        // BufferListCopyConstructor
        cout << "\nTest case: BufferList class: Copy constructor:\n";
        
        BufferList bufferList(5);
        for (int i=40;i>0;i--)
            bufferList.enqueue(i);

        if (tester.BufferListCopyConstructor(bufferList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        cout << "\nTest case: Bufferlist class: Checking that empty buffers are cleared\n";
        BufferList bufferList(5);
        for (int i=0;i<=10;i++)
            bufferList.enqueue(i);
        if(tester.BufferListDequeueClearEmptyBuffer(bufferList))
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
    

    Buffer newBuffer(buffer);

    // Same capacity?
    if(newBuffer.capacity() != buffer.capacity()) return false;

    // Different buffer pointers?
    if(newBuffer.capacity() > 1){
        if(newBuffer.m_buffer == buffer.m_buffer) return false;
    }

    // Same start and end?
    if(newBuffer.m_start != buffer.m_start) return false;
    if(newBuffer.m_end != buffer.m_end) return false;

    // Same values in buffer?
    for(int i = 0; i < newBuffer.capacity(); i++){
        if(newBuffer.m_buffer[i] != buffer.m_buffer[i]){
            return false;
        }
    }

    return true;

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

bool Tester::BufferListEnqueueDequeue(BufferList& bufferList, int dataCount){
    try{
        for (int i=0;i<dataCount;i++) {
            bufferList.enqueue(i); 
        }

        for (int i=0;i<dataCount;i++) {
            bufferList.dequeue(); 
        }
    // Neither of these exceptions should occur    
    }catch(overflow_error &e){
        return false;
    }catch(underflow_error &e){
        return false;
    }

    return true;
}

bool Tester::BufferListDequeueEmpty(BufferList& bufferList){
    try{
        bufferList.dequeue();
    }catch(std::underflow_error &e){
        //Expected error
        return true;
    }catch(...){
        return false;
    }
    return false;
}

bool Tester::BufferListCopyConstructor(const BufferList &copyBuffer){

    BufferList newBufferList(copyBuffer);

    // Same size?
    if(newBufferList.m_listSize != copyBuffer.m_listSize) return false;
    // Same minimum capacity?
    if(newBufferList.m_minBufCapacity != copyBuffer.m_minBufCapacity) return false;


    // Memory in linked list different?
    if(newBufferList.m_listSize > 0){

        Buffer* lhsBuffer = newBufferList.m_cursor;
        Buffer* rhsBuffer = copyBuffer.m_cursor;
        
        for(int i = 0; i < newBufferList.m_listSize; ++i){
            // Points to the same memory, indicates failed deep copy
            if(lhsBuffer == rhsBuffer){
                return false;
            }

            // Same capacity?
            if(lhsBuffer->capacity() != rhsBuffer->capacity()) return false;

            // Different buffer pointers?
            if(lhsBuffer->capacity() > 1){
                // Points to the same memory, indicates failed deep copy
                if(lhsBuffer->m_buffer == rhsBuffer->m_buffer) return false;
            }

            // Same start and end?
            if(lhsBuffer->m_start != rhsBuffer->m_start) return false;
            if(lhsBuffer->m_end != rhsBuffer->m_end) return false;

            
            // Same values in buffer?
            for(int i = 0; i < lhsBuffer->capacity(); i++){
                if(lhsBuffer->m_buffer[i] != rhsBuffer->m_buffer[i]){
                    return false;
                }
            }
     
            if(lhsBuffer->m_next != nullptr && rhsBuffer->m_next != nullptr){
                lhsBuffer = lhsBuffer->m_next;
                rhsBuffer = rhsBuffer->m_next;
            }
     
        }
    }

    return true;


}

bool Tester::BufferListAssignmentConstructor(const BufferList &rhsBufferList){

    /*
         "To check whether it created a deep copy, we can clear the rhs object 
         and check that the data is preserved in the current object by calling dequeue."

         These instructions are a little vauge. How do we check if data is being preserved if the
         rhs is cleared? What are we comparing it to? What do we do with the values retrieved from
         dequeue?

    */



    BufferList lhsBufferList(0);

    lhsBufferList = rhsBufferList;

    // Same size?
    if(lhsBufferList.m_listSize != rhsBufferList.m_listSize) return false;
    // Same minimum capacity?
    if(lhsBufferList.m_minBufCapacity != rhsBufferList.m_minBufCapacity) return false;


    // Memory in linked list different?
    if(lhsBufferList.m_listSize > 0){

        Buffer* lhsBuffer = lhsBufferList.m_cursor;
        Buffer* rhsBuffer = rhsBufferList.m_cursor;
        
        for(int i = 0; i < lhsBufferList.m_listSize; ++i){
            // Points to the same memory, indicates failed deep copy
            if(lhsBuffer == rhsBuffer){
                return false;
            }

            // Same capacity?
            if(lhsBuffer->capacity() != rhsBuffer->capacity()) return false;

            // Different buffer pointers?
            if(lhsBuffer->capacity() > 1){
                // Points to the same memory, indicates failed deep copy
                if(lhsBuffer->m_buffer == rhsBuffer->m_buffer) return false;
            }

            // Same start and end?
            if(lhsBuffer->m_start != rhsBuffer->m_start) return false;
            if(lhsBuffer->m_end != rhsBuffer->m_end) return false;

            
            // Same values in buffer?
            for(int i = 0; i < lhsBuffer->capacity(); i++){
                if(lhsBuffer->m_buffer[i] != rhsBuffer->m_buffer[i]){
                    return false;
                }
            }
     
            if(lhsBuffer->m_next != nullptr && rhsBuffer->m_next != nullptr){
                lhsBuffer = lhsBuffer->m_next;
                rhsBuffer = rhsBuffer->m_next;
            }
     
        }
    }

    return true;


}

void Tester::BufListEnqueuePerformance(int numTrials, int N){
    
    int num_doublings = 5; // Arbitrary

    for(int i = 0; i < num_doublings; i++){
        clock_t c_start, c_end;

        c_start = clock();
        auto t0 = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < numTrials; ++i){
            BufferList bufferList(0);
            BufferListEnqueueDequeue(bufferList, N);
            bufferList.clear();
        }

        c_end = clock();
        auto t1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0);

        double time_taken = double(c_end - c_start) / double(CLOCKS_PER_SEC);
        std::cout << "Inserting " << N << " members(" << numTrials << " trials) took " << double(c_end - c_start) << " clock ticks (" << time_taken << " seconds)!" << std::endl;
        std::cout << "(high_resolution_clock diff): " << time_span.count() << '\n';
        std::cout << std::endl;
        
        N = N * 2;
    }
}

bool Tester::BufferListDequeueClearEmptyBuffer(BufferList &bufferlist){

    bufferlist.dump();
    int listSizePrev = bufferlist.m_listSize;

    for(int i = 0; i < 5; i++)
    bufferlist.dequeue();

    int listSizeCurr = bufferlist.m_listSize;
    bufferlist.dump();

    if(listSizePrev - listSizeCurr == 1) return true;
    return false;

}
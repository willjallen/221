// driver.cpp: sample driver for the RQueue class.

#include "rqueue.h"
using namespace std;
// Priority functions compute an integer priority for a student. Internal
// computations may be floating point, but must return an integer.

int priorityFn1(const Student &tudent);
int priorityFn2(const Student &student);



class Tester {
public:
  bool RQueueTestCopyConstructor();
  bool RQueueTestAssingmentOperator();
  bool RQueueTestInsertDifferentPriorityFn();
  bool RQueueTestGetNextStudentEmptyQueue();

};



bool Tester::RQueueTestCopyConstructor(){
  RQueue queue1(priorityFn1);
  Student student3("Nick",2,0,0,0);
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student4("Eva",4,3,2,1);

  queue1.insertStudent(student3);
  queue1.insertStudent(student1);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);

  queue1.dump();
  cout << endl;

  RQueue queue2(queue1);

  cout << "lhs queue" << endl;
  queue1.dump();
  cout << endl;

  cout << "rhs queue" << endl;
  queue2.dump();
  cout << endl;

  if(&queue1 == &queue2) return false;
  if(queue1._heap == queue2._heap) return false;
  if(queue1.priority != queue2.priority) return false;
  if(queue1._size != queue2._size) return false;


  return true;

} 

bool Tester::RQueueTestAssingmentOperator(){
  RQueue queue1(priorityFn1);
  RQueue queue2(priorityFn1);

  // Create some test students and insert them into the queue
  //Student(string name, int priority, int year, int major, int group)
  Student student3("Nick",2,0,0,0);
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student4("Eva",4,3,2,1);

  queue1.insertStudent(student3);
  queue1.insertStudent(student1);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);

  Student student5("John",6,3,2,1);
  Student student6("Mia",3,0,0,0);

  queue2.insertStudent(student5);
  queue2.insertStudent(student6);


  queue1 = queue2;

  cout << "lhs queue" << endl;
  queue1.dump();
  cout << endl;

  cout << "rhs queue" << endl;
  queue2.dump();
  cout << endl;

  if(&queue1 == &queue2) return false;
  if(queue1._heap == queue2._heap) return false;
  if(queue1.priority != queue2.priority) return false;
  if(queue1._size != queue2._size) return false;

  return true;

}

bool Tester::RQueueTestInsertDifferentPriorityFn(){
  RQueue queue1(priorityFn1);
  RQueue queue2(priorityFn2);

  // Create some test students and insert them into the queue
  //Student(string name, int priority, int year, int major, int group)
  Student student3("Nick",2,0,0,0);
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student4("Eva",4,3,2,1);

  queue1.insertStudent(student3);
  queue1.insertStudent(student1);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);

  Student student5("John",6,3,2,1);
  Student student6("Mia",3,0,0,0);

  queue2.insertStudent(student5);
  queue2.insertStudent(student6);

  try{
    queue1.mergeWithQueue(queue2);
  }catch(std::domain_error& e){
    return true;
  }

  return false;


}

bool Tester::RQueueTestGetNextStudentEmptyQueue(){
  RQueue queue1(priorityFn1);
  Student student1("Sam",1,1,1,1);
  queue1.insertStudent(student1);

  queue1.getNextStudent();

  try{
    queue1.getNextStudent();
  }catch(std::domain_error& e){
    return true;
  }

  return false;
}


int main() {

  RQueue queue1(priorityFn1);
  RQueue queue2(priorityFn1);

  // Create some test students and insert them into the queue
  //Student(string name, int priority, int year, int major, int group)
  Student student3("Nick",2,0,0,0);
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student4("Eva",4,3,2,1);

  queue1.insertStudent(student3);
  queue1.insertStudent(student1);
  queue1.insertStudent(student2);
  queue1.insertStudent(student4);

  std::cout << "\nqueue1 dump after inserting 4 students (Nick, Sam, Liz, Eva):" << std::endl;
  queue1.dump();

  Student student5("John",6,3,2,1);
  Student student6("Mia",3,0,0,0);

  queue2.insertStudent(student5);
  queue2.insertStudent(student6);

  std::cout << "\nqueue2 dump after inserting 2 students (John, Mia):" << std::endl;
  queue2.dump();

  queue1.mergeWithQueue(queue2);

  // Print the queue, change priority function, print again, change
  // again, print again.  Changing the priority function should cause
  // the heap to be rebuilt.

  std::cout << std::endl << "Contents of queue1 after merging with queue2:\n";
  queue1.printStudentQueue();
  std::cout << "\nDump queue1 after merging with queue2:\n";
  queue1.dump();
  
  queue1.setPriorityFn(priorityFn2);

  std::cout << std::endl << "Contents of queue1 after changing the priority function to priorityFn2:\n";
  queue1.printStudentQueue();
  std::cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
  queue1.dump();
  
  queue1.setPriorityFn(priorityFn1);

  std::cout << std::endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
  queue1.printStudentQueue();
  std::cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
  queue1.dump();

  // Remove and print students in priority order

  std::cout << "\nFinal queue1 in priority order:\n";
  while (queue1.numStudents() > 0) {
    Student student = queue1.getNextStudent();
    std::cout << "[" << priorityFn1(student) << "] " << student << std::endl;
  }


  Tester tester;

  std::cout << "\nTesting copy constructor..." << std::endl;
  if(tester.RQueueTestCopyConstructor()){
    std::cout << "test passed" << endl;
  }else{
    std::cout << "test failed" << endl;
  }


  std::cout << "\nTesting assignment operator..." << std::endl;
  if(tester.RQueueTestAssingmentOperator()){
    std::cout << "test passed" << endl;
  }else{
    std::cout << "test failed" << endl;
  }


  std::cout << "\nTesting insert w/ different priority function..." << std::endl;
  if(tester.RQueueTestInsertDifferentPriorityFn()){
    std::cout << "test passed" << endl;
  }else{
    std::cout << "test failed" << endl;
  }



  std::cout << "\nTesting remove from empty queue..." << std::endl;
  if(tester.RQueueTestGetNextStudentEmptyQueue()){
    std::cout << "test passed" << endl;
  }else{
    std::cout << "test failed" << endl;
  }





  return 0;
}

int priorityFn1(const Student&student) {
  //priority value is determined based on some criteria
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  int priority = student.getYear() + student.getMajor() + student.getGroup();
  return priority;
}

int priorityFn2(const Student&student) {
  //priority is determined by an officer in registrar office
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  return student.getPriority();
}
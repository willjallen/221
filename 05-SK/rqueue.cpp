// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  this->priority = priFn;
  this->_size = 0;
  this->_heap = nullptr;

}

RQueue::~RQueue()
{
  clear();
}

RQueue::RQueue(const RQueue& rhs)
{  
  *this = rhs; //???
}


RQueue& RQueue::operator=(const RQueue& rhs) {
    if(this != &rhs) {
        clear();
        copyTree(_heap, rhs._heap);
    }
    return *this;
}


void RQueue::copyTree(Node*& dest, Node* src) {
    if(src == nullptr) return;
    dest = new Node(*src);
    copyTree(dest->_left, src->_left);
    copyTree(dest->_right, src->_right);
}


void RQueue::insertStudent(const Student& input) {
  /************************
   * To be implemented
   * *********************/
  // cout << "in insert" << endl;
  // if(this->_heap == nullptr){
  //   cout << "xxthis->_heap (lhs): nullptr" << endl;
  // }else{
  //   cout << "xxthis->_heap (lhs): " << _heap->getStudent() << endl;
  // }

 // If heap is empty
  if(this->_heap == nullptr){
    this->_heap = new Node(input);
  }else{
    Node* insertNode = new Node(input);
    this->_heap = mergeWithQueue(this->_heap, insertNode);
  }

  this->_size++;

  // cout << endl;
  // cout << "dump:" << endl;
  dump();
  // cout << endl;



}

Student RQueue::getNextStudent() {
  /************************
   * To be implemented
   * *********************/

  // If the queue is empty, throw domain error
  if(_heap == nullptr){
    throw domain_error("Queue is empty");
  }


  // Get the node to be returned
  Node* rtnNode = _heap;

  // Get the student of the node to be returned
  Student rtnStudent = _heap->getStudent();

  // Get the left and right members of the node to merge
  Node* leftNode = rtnNode->_left;
  Node* rightNode = rtnNode->_right;


  dump();
  cout << endl;
  // If this is the last item in the queue
  if(_size == 1){
    delete _heap;
    this->_heap = nullptr;
    _size = 0;
  }else{
    this->_heap = mergeWithQueue(leftNode, rightNode);
    _size--;
    delete rtnNode;
  }


  cout << this->_heap << endl;
  return rtnStudent;
}


void RQueue::mergeWithQueue(RQueue& rhs) {
  /************************
   * To be implemented
   * *********************/

  cout << "Merging:" << endl;
  if(this->_heap == nullptr){
    cout << "this->_heap (lhs): nullptr" << endl;
  }else{
    cout << "this->_heap (lhs): " << _heap->getStudent() << endl;
  }
  cout << "(rhs) " << rhs._heap->getStudent() << endl;

  /*
  Two skew heaps can only be merged if they have the same priority 
  function. If they do not, throw domain_eror
  */
  if(this->getPriorityFn() != rhs.getPriorityFn()){
    throw domain_error("Different priority functions");
  }


  /*
  This function requires protection against self-merging. 
  Merging a heap with itself is not allowed.
  */
  if(this == &rhs){
    throw domain_error("Self-merge"); //???
  }

  cout << this->_size << endl;
  cout << rhs._size << endl;
  this->_size += rhs._size;


  this->_heap = mergeWithQueue(this->_heap, rhs._heap);
  // cout << this->_heap->getStudent() << endl;
  // cout << this->_heap->_left->getStudent() << endl;
  // cout << this->_heap->_right << endl;

  // Set rhs to be empty
  rhs._heap = nullptr;

  cout << endl;

}

Node* RQueue::mergeWithQueue(Node* heapOneRoot, Node* heapTwoRoot) {

  cout << "==========" << endl;
  cout << "Merging" << endl;
  if(heapOneRoot != nullptr){
    cout << "heapOneRoot: " << heapOneRoot->getStudent() << endl;
  }else{
    cout << "heapOneRoot: nullptr" << endl;
  }
  if(heapTwoRoot != nullptr){
    cout << "heapTwoRoot: " << heapTwoRoot->getStudent() << endl;
  }else{
    cout << "heapTwoRoot: nullptr" << endl;
  }
  

  // If p1 is Null, return p2; similarly, if p2 is Null, return p1. 
  if(heapOneRoot == nullptr){
    return heapTwoRoot;
  }
  
  if(heapTwoRoot == nullptr){
    return heapOneRoot;
  }

  // Assume that p1 has higher priority than p2; if not, swap, p1 and p2. 
  // "Higher" actually means less here (0 is higher than 1)
  // Because it makes sense, okay

  if(priority(heapOneRoot->getStudent()) > priority(heapTwoRoot->getStudent())){
    cout << "Swapping" << endl;
    swap(heapOneRoot, heapTwoRoot);
    cout << "After swap:" << endl;
    cout << "heapOneRoot: " << heapOneRoot->getStudent() << endl;
    cout << "heapTwoRoot: " << heapTwoRoot->getStudent() << endl;

  }


  // Swap the left and right subtrees of heapOneRoot 
  if(heapOneRoot->_left == nullptr && heapOneRoot->_right == nullptr){
    // Do nothing
    // cout << "should be here "<< endl;
  }else if(heapOneRoot->_left == nullptr){

    heapOneRoot->_left = heapOneRoot->_right;
    heapOneRoot->_right = nullptr;

  }else if(heapOneRoot->_right == nullptr){

    heapOneRoot->_right = heapOneRoot->_left;
    heapOneRoot->_left = nullptr; 

  }else{

    swap(heapOneRoot->_left, heapOneRoot->_right);

  }

  // cout << "here" << endl;
  // Recursively merge p2 and the left subtree of p1, replacing the left subtree of p1 with the result of the recursive merge.
  heapOneRoot->_left = mergeWithQueue(heapTwoRoot, heapOneRoot->_left);

  cout << "==========" << endl;
  cout << endl << endl;
  cout << "returning: " << endl;
  cout << "heapOneRoot: " << heapOneRoot->getStudent() << endl;
  cout << heapOneRoot->_left << endl;
  cout << heapOneRoot->_right << endl;

  return heapOneRoot;


}

// Cant just swap pointers, swap student info & children
void RQueue::swap(Node*& nodeOne, Node*& nodeTwo){

  // cout << nodeOne->getStudent() << endl;
  // cout << nodeTwo->getStudent() << endl;

  // Student tempStudent = nodeOne->getStudent();
  // Node*& nodeOneLeft = nodeOne->_left;
  // Node*& nodeOneRight = nodeOne->_right;

  // nodeOne->_student = nodeTwo->getStudent();
  // nodeOne->_left = nodeTwo->_left;
  // nodeOne->_right = nodeTwo->_right;

  // nodeTwo->_student = tempStudent;
  // nodeTwo->_left = nodeOneLeft;
  // nodeTwo->_right = nodeOneRight;

  Node* tempNode = nodeOne;
  nodeOne = nodeTwo;
  nodeTwo = tempNode;

}

void RQueue::rebuildHeap(){

  int size = _size;
  Student* tempArray = new Student[size];
  int index = 0;
  fillArray(tempArray, index, _heap);
  clear();

  cout << "filled?" << endl;
  // Insert all elements again with new priority function
  for(int i = 0; i < size; i++){
    cout << "i: " << i << endl;
    cout << tempArray[i] << endl;
    insertStudent(tempArray[i]);
    cout << "done?" << endl;
  }

  delete[] tempArray;

}


void RQueue::fillArray(Student*& arr, int& indx, Node* node){
  // Preorder
  if(node == nullptr) return;

  fillArray(arr, indx, node->_left);
  arr[indx] = node->getStudent();
  indx++;
  fillArray(arr, indx, node->_right);
}


void RQueue::clear() {
  if(_heap != nullptr){
    cout << _heap->getStudent() << endl;
  }
 clear(_heap);
 _heap = nullptr;
 _size = 0;
}

void RQueue::clear(Node* node) {
    if(node == nullptr) return;
    clear(node->_left);
    clear(node->_right);
    delete node;
}

int RQueue::numStudents() const
{
  return this->_size;
}

void RQueue::printStudentQueue() const {
  /************************
   * To be implemented
   * *********************/
  printStudentQueue(_heap); // ???
}

// Preorder traversal
void RQueue::printStudentQueue(Node* node) const {
  if(node == nullptr) return;
// [0] Student: Nick, priority: 2, year: 0, major: CS, group: Minority
  cout << "[" << priority(node->getStudent()) << "] " << node->getStudent() << endl;
  printStudentQueue(node->_left);
  printStudentQueue(node->_right);
}


prifn_t RQueue::getPriorityFn() const {
  return this->priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  /************************
   * To be implemented
   * *********************/
  this->priority = priFn;
  rebuildHeap();
}


// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    // cout << pos->_student << endl;
    cout << "(";
    dump(pos->_left);
    // cout << pos->_student;
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}
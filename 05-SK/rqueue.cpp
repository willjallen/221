// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  this->priority = priFn;
  this->size = 0;

}

RQueue::~RQueue()
{
  clear();
  this->size = 0;

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


void DTree::copyTree(Node*& dest, Node* src) {
    if(src == nullptr) return;
    dest = new Node(*src);
    copyTree(dest->_left, src->_left);
    copyTree(dest->_right, src->_right);
}


void RQueue::insertStudent(const Student& input) {
  /************************
   * To be implemented
   * *********************/
}

Student RQueue::getNextStudent() {
  /************************
   * To be implemented
   * *********************/
}


void RQueue::mergeWithQueue(RQueue& rhs) {
  /************************
   * To be implemented
   * *********************/
}

void RQueue::clear() {
 clear(_heap);
}

void RQueue::clear(DNode* node) {
    if(node == nullptr) return;
    clear(node->_left);
    clear(node->_right);
    delete node;
}

int RQueue::numStudents() const
{
  /************************
   * To be implemented
   * *********************/
}

void RQueue::printStudentQueue() const {
  /************************
   * To be implemented
   * *********************/
  print(_heap); // ???
}

void RQueue::print(Node *pos){
    if ( pos != nullptr ) {
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_left);
    dump(pos->_right);
  }

}

prifn_t RQueue::getPriorityFn() const {
  return this->priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  /************************
   * To be implemented
   * *********************/
  this->priority = priFn;
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
    cout << "(";
    dump(pos->_left);
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
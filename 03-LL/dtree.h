/**
 * Project 2 - Binary Trees
 * DiscriminatorTree.h
 * An interface for the DTree class.
 */

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

#define DEFAULT_USERNAME ""
#define INVALID_DISC -1
#define MIN_DISC 0000
#define MAX_DISC 9999
#define DEFAULT_BADGE ""
#define DEFAULT_STATUS ""

#define DEFAULT_SIZE 1
#define DEFAULT_NUM_VACANT 0

class Grader;   /* For grading purposes */
class Tester;   /* Forward declaration for testing class */


class Account {
public:
    friend class Grader;
    friend class Tester;
    friend class DNode;
    friend class DTree;
    Account() {
        _username = DEFAULT_USERNAME;
        _disc = INVALID_DISC;
        _nitro = false;
        _badge = DEFAULT_BADGE;
        _status = DEFAULT_STATUS;
    }

    Account(string username, int disc, bool nitro, string badge, string status) {
        if(disc < MIN_DISC || disc > MAX_DISC) {
            throw std::out_of_range("Discriminator out of valid range (" + std::to_string(MIN_DISC) 
                                    + "-" + std::to_string(MAX_DISC) + ")");
        }
        _username = username;
        _disc = disc;
        _nitro = nitro;
        _badge = badge;
        _status = status;
    }

    /* Getters */
    string getUsername() const {return _username;}
    int getDiscriminator() const {return _disc;}
    bool hasNitro() const {return _nitro;}
    string getBadge() const {return _badge;}
    string getStatus() const {return _status;}

private:
    string _username;
    int _disc;
    bool _nitro;
    string _badge;
    string _status;
};

/* Overloaded << operator to print Accounts */
ostream& operator<<(ostream& sout, const Account& acct);

class DNode {
    friend class Grader;
    friend class Tester;
    friend class DTree;

public:
    DNode() {
        _size = DEFAULT_SIZE;
        _numVacant = DEFAULT_NUM_VACANT;
        _vacant = false;
        _left = nullptr;
        _right = nullptr;
    }

    DNode(Account account) {
        _account = account;
        _size = DEFAULT_SIZE;
        _numVacant = DEFAULT_NUM_VACANT;
        _vacant = false;
        _left = nullptr;
        _right = nullptr;
    }

    /* Getters */
    Account getAccount() const {return _account;}
    int getSize() const {return _size;}
    int getNumVacant() const {return _numVacant;}
    bool isVacant() const {return _vacant;}
    string getUsername() const {return _account.getUsername();}
    int getDiscriminator() const {return _account.getDiscriminator();}

private:
    Account _account;
    int _size;
    int _numVacant;
    bool _vacant;
    DNode* _left;
    DNode* _right;

    /* IMPLEMENT (optional): any other helper functions */
};

typedef struct treeArray{
    int size = 0;
    DNode* array;

    treeArray(int size){
        this->size = size;
        this->array = new DNode[size];
    }

    ~treeArray(){
        delete[] array;
    }

} TreeArray;


typedef struct bisectedArray{
    DNode* leftArray;
    int leftArraySize = 0;

    DNode* rightArray;
    int rightArraySize = 0;

    DNode* rootNode;

    bisectedArray(DNode* leftArray, int leftArraySize, DNode* rightArray, int rightArraySize, DNode* rootNode) : leftArray(leftArray), leftArraySize(leftArraySize), rightArray(rightArray), rightArraySize(rightArraySize), rootNode(rootNode) {}
   
   ~bisectedArray(){
        delete[] leftArray;
        delete[] rightArray;
   }

} BisectedArray;

class DTree {
    friend class Grader;
    friend class Tester;

public:
    DTree(): _root(nullptr) {}

    /* IMPLEMENT: destructor and assignment operator*/
    ~DTree();
    DTree& operator=(const DTree& rhs);

    /* IMPLEMENT: Basic operations */

    bool insert(Account newAcct);
    bool remove(int disc, DNode*& removed);
    DNode* retrieve(int disc);
    void clear();
    void printAccounts() const;
    void dump() const {dump(_root);}
    void dump(DNode* node) const;

    /* IMPLEMENT: "Helper" functions */
    bool recursiveInsert(DNode* node, Account newAcct);
    DNode* recursiveSearch(DNode* node, int disc);
    bool recursiveRemove(DNode* node, int disc, DNode*& removed);
    void recursiveClear(DNode* node);
    bool updateAndRebanceAlongPath(int disc);
    void recursiveUpdateAndRebanceAlongPath(DNode* node, int disc);
    void updateAndRebalanceNode(DNode* node);
    

    int getNumUsers() const;
    string getUsername() const {return _root->getUsername();}
    void updateSize(DNode* node);
    void updateNumVacant(DNode* node);
    bool checkImbalance(DNode* node);
    //----------------
    void rebalance(DNode*& node);
    // -- OR --
    // DNode* rebalance(DNode* node);
    //----------------

private:


    DNode* _root;

    /* IMPLEMENT (optional): any additional helper functions here */
    std::shared_ptr<TreeArray> treeToArray(DNode* node);
    void arrayToTree(DNode* node, std::shared_ptr<TreeArray> arr);
    void recursiveArrayToTree(DNode* node, std::shared_ptr<BisectedArray> bArray);
    void recursiveTreeToArray(DNode* node, DNode* arr, int& itr);

    std::shared_ptr<BisectedArray> bisectArray(DNode* array, int size);

};
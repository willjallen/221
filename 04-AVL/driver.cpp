#include "dtree.h"
#include <random>
#include <stdexcept>


#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);

    bool testUTreeClear(DTree& dtree);

    bool testUTreeInsertIntoEmptyTree(DTree& dtree);
    bool testUTreeDuplicateInsert(DTree& dtree);
    bool testUTreeInsertIntoVacantNode(DTree& dtree);
    
    bool testUTreeRemoveNonExistentNode(DTree& dtree);
    bool testUTreeRemoveVacantNode(DTree& dtree);

    bool testUTreeDeepCopy(DTree& dtree);

    bool testUTreeSearch(DTree& dtree);

    bool testUTreeBalanced(DTree& dtree, int numInsertions);
    void testUTreeBalancedHelper(DTree& dtree, DNode* node, bool& returnStatus);
    // bool testDTreeBalancedLeftOnlyInsert(DTree& dtree, int numInsertions);
    // bool testDTreeBalancedRightOnlyInsert(DTree& dtree, int numInsertions);
    // bool testDTreeBalancedAllNodesRemoved(DTree& dtree);

    bool testUTreeBSTProperty(DTree& dtree, int numInsertions);
    void testUTreeBSTPropertyHelper(DNode* node, bool& returnStatus);

};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}


bool Tester::testBasicDTreeRemove(DTree& dtree) {
    bool allRemoved = true;
    int numDiscriminators = 3;
    int discriminators[] = {207, 251, 883};
    DNode* removed = nullptr;

    for(int i = 0; i < numDiscriminators; i++) {
        if(!dtree.remove(discriminators[i], removed)) {
            cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
        }
    }

    cout << "Dumping the tree after 3 deletions time" << endl;
    dtree.dump();
    cout << endl;

    cout << "Inserting 1 element to cause an imbalance and to clear vacant nodes" << endl;
    Account bigAcct = Account("", 9999, 0, "", "");
    dtree.insert(bigAcct);
    return allRemoved;
}



// bool Tester::testUTreeClear(DTree& dtree){
//     for(int i = 0; i < NUMACCTS; i++) {
//         int disc = RANDDISC;
//         Account newAcct = Account("", disc, 0, "", "");
//         dtree.insert(newAcct);
//     }

//     dtree.clear();

//     if(dtree.getTreeSize() != 0){
//         return false;
//     }

//     if(dtree._root != nullptr){
//         return false;
//     }

//     return true;
// }

// bool Tester::testUTreeInsertIntoEmptyTree(DTree& dtree){
//     bool status = true;

//     dtree.clear();
//     Account newAcct = Account("", 1111, 0, "", "");
//     if(!dtree.insert(newAcct)) status = false;

//     if(dtree._root->getDiscriminator() != 1111) status = false;
//     return status;
// }

// bool Tester::testUTreeRemoveNonExistentNode(DTree& dtree){
//     bool status = true;

//     dtree.clear();
//     Account newAcct = Account("", 0, 0, "", "");
//     if(!dtree.insert(newAcct)) status = false;

//     newAcct = Account("", 1, 0, "", "");
//     if(!dtree.insert(newAcct)) status = false;

//     newAcct = Account("", 2, 0, "", "");
//     if(!dtree.insert(newAcct)) status = false;
//     DNode* node;
//     if(dtree.remove(3, node) != false) status = false;

//     return status;
// }




int main() {
    Tester tester;

    /* Basic dtree tests */
    DTree dtree;

    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;

    cout << "\n\nTesting UTree clear..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }


    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }


    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester.testBasicDTreeRemove(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }








    return 0;
}

#include "dtree.h"
#include "utree.h"
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

    bool testBasicUTreeInsertSameUsername(UTree& utree);
    bool testBaiscUTreeRemove(UTree& utree);

    void UTreeLoadData(UTree& utree);

    bool testUTreeClear(UTree& utree);

    bool testUTreeInsertIntoEmptyTree(UTree& utree);
    bool testUTreeDuplicateInsert(UTree& utree);
    bool testUTreeInsertIntoVacantNode(UTree& utree);
    
    bool testUTreeRemoveNonExistentNode(UTree& utree);
    bool testUTreeRemoveVacantNode(UTree& utree);

    bool testUTreeDeepCopy(UTree& utree);

    bool testUTreeSearch(UTree& utree);

    bool testUTreeBalanced(UTree& utree, int numInsertions);
    void testUTreeBalancedHelper(UTree& utree, DNode* node, bool& returnStatus);
    // bool testDTreeBalancedLeftOnlyInsert(DTree& dtree, int numInsertions);
    // bool testDTreeBalancedRightOnlyInsert(DTree& dtree, int numInsertions);
    // bool testDTreeBalancedAllNodesRemoved(DTree& dtree);

    bool testUTreeBSTProperty(DTree& dtree, int numInsertions);
    void testUTreeBSTPropertyHelper(DNode* node, bool& returnStatus);

};

// bool Tester::testBasicDTreeInsert(DTree& dtree) {
//     bool allInserted = true;
//     for(int i = 0; i < NUMACCTS; i++) {
//         int disc = RANDDISC;
//         Account newAcct = Account("", disc, 0, "", "");
//         if(!dtree.insert(newAcct)) {
//             cout << "Insertion on node " << disc << " did not return true" << endl;
//             allInserted = false;
//         }
//     }
//     return allInserted;
// }


// bool Tester::testBasicDTreeRemove(DTree& dtree) {
//     bool allRemoved = true;
//     int numDiscriminators = 3;
//     int discriminators[] = {207, 251, 883};
//     DNode* removed = nullptr;

//     for(int i = 0; i < numDiscriminators; i++) {
//         if(!dtree.remove(discriminators[i], removed)) {
//             cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
//         }
//     }

//     cout << "Dumping the tree after 3 deletions time" << endl;
//     dtree.dump();
//     cout << endl;

//     cout << "Inserting 1 element to cause an imbalance and to clear vacant nodes" << endl;
//     Account bigAcct = Account("", 9999, 0, "", "");
//     dtree.insert(bigAcct);
//     return allRemoved;
// }


bool Tester::testUTreeInsertIntoEmptyTree(UTree& utree){
    bool status = true;

    utree.clear();
    Account newAcct = Account("nice", 1111, 0, "", "");
    if(!utree.insert(newAcct)) status = false;

    if(utree._root->getUsername() != "nice") status = false;
    return status;
}

bool Tester::testBasicUTreeInsertSameUsername(UTree& utree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("cool", disc, 0, "", "");
        if(!utree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testUTreeDuplicateInsert(UTree& utree){
    utree.clear();

    Account newAcct = Account("nice", 1111, 0, "", "");
    utree.insert(newAcct);
    return !(utree.insert(newAcct));
}

void Tester::UTreeLoadData(UTree& utree){
    utree.loadData("accounts.csv", false);
}

bool Tester::testUTreeClear(UTree& utree){
    UTreeLoadData(utree);
    utree.clear();

    if(utree._root != nullptr){
        return false;
    }

    return true;
}





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
    // DTree dtree;
    UTree utree;

    cout << "Testing UTree insertion w/ same username..." << endl;
    if(tester.testBasicUTreeInsertSameUsername(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    utree.dump();
    cout << endl;


    cout << "\n\nTesting UTree insertion into empty tree..." << endl;
    if(tester.testUTreeInsertIntoEmptyTree(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting UTree duplicate insertion..." << endl;
    if(tester.testUTreeDuplicateInsert(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(utree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "Resulting DTree:" << endl;
    // dtree.dump();
    // cout << endl;

    cout << "\n\nTesting UTree loadData..." << endl;
    tester.UTreeLoadData(utree);
    utree.dump();
    cout << endl;


    cout << "\n\nTesting UTree clear..." << endl;
    if(tester.testUTreeClear(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }


    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }


    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "\n\nTesting DTree deletion..." << endl;
    // if(tester.testBasicDTreeRemove(dtree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }








    return 0;
}

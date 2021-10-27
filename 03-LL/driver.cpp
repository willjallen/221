#include "dtree.h"
#include <random>

#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999); 

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);

    bool testDTreeClear(DTree& dtree);

    bool testDTreeInsertIntoEmptyTree(DTree& dtree);
    
    bool testDTreeRemoveNonExistentNode(DTree& dtree);
    bool testDTreeRemoveVacantNode(DTree& dtree);

    void testDTreeTreeToArray(DTree& dtree);
    bool testDTreeDeepCopy(DTree& dtree);
    bool testDTreeSearch(DTree& dtree);

    bool testDTreeBalanced(DTree& dtree, int numInsertions);
    void testDTreeBalancedHelper(DTree& dtree, DNode* node, bool& returnStatus);

    bool testDTreeBSTProperty(DTree& dtree);
    bool testDTreeBSTPropertyHelper(DNode* node);

    void DTreeShotgunTest(DTree& dtree, int insertSize, int deleteSize, int totalSize);

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
    int discriminators[] = {8735, 3516, 1271};
    DNode* removed = nullptr;

    for(int i = 0; i < numDiscriminators; i++) {
        if(!dtree.remove(discriminators[i], removed)) {
            cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
            allRemoved = false;
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

bool Tester::testDTreeClear(DTree& dtree){
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }

    dtree.clear();

    if(dtree.getTreeSize() != 0){
        return false;
    }

    if(dtree._root != nullptr){
        return false;
    }

    return true;
}

bool Tester::testDTreeInsertIntoEmptyTree(DTree& dtree){
    bool status = true;

    dtree.clear();
    Account newAcct = Account("", 1111, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    if(dtree._root->getDiscriminator() != 1111) status = false;
    return status;
}

bool Tester::testDTreeRemoveNonExistentNode(DTree& dtree){
    bool status = true;

    dtree.clear();
    Account newAcct = Account("", 0, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    newAcct = Account("", 1, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    newAcct = Account("", 2, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;
    DNode* node;
    if(dtree.remove(3, node) != false) status = false;

    return status;
}

bool Tester::testDTreeRemoveVacantNode(DTree& dtree){
    bool status = true;

    dtree.clear();
    Account newAcct = Account("", 0, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    newAcct = Account("", 1, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    newAcct = Account("", 2, 0, "", "");
    if(!dtree.insert(newAcct)) status = false;

    DNode* node;
    if(!dtree.remove(2, node)) status = false;

    if(dtree.remove(2, node) != false) status = false;

    return status;
}

void Tester::testDTreeTreeToArray(DTree& dtree){
    dtree.clear();

    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }

    cout << "Tree dump:" << endl;
    dtree.dump();
    cout << endl;

    cout << "Tree:" << endl;
    TreeArray* treeArr = dtree.treeToArray(dtree._root);
    for(int i = 0; i < treeArr->size; ++i){
        cout << treeArr->array[i].getDiscriminator() << ", ";
    }
    cout << endl;
    delete treeArr;
}

bool Tester::testDTreeDeepCopy(DTree& dtree){
    cout << "rhs dump:" << endl;
    dtree.dump();
    cout << endl;

    DTree newTree;
    newTree = dtree;
    cout << "new tree dump:" << endl;
    newTree.dump();
    cout << endl;

    cout << "checking _root pointers are different" << endl;
    if(dtree._root != newTree._root){
        cout << "success" << endl;
        return true;
    }
    cout << "fail" << endl;
    cout << dtree._root << endl;
    cout << newTree._root << endl;
    return false;
}

bool Tester::testDTreeSearch(DTree& dtree){
    dtree.clear();
    for(int i = 0; i < 100; i++){
        dtree.insert(Account("", i, 0, "", ""));
    }


    for(int i = 0; i < 100; i++){
        if(!dtree.retrieve(i)){
            return false;
        }
    }

    return true;

    dtree.dump();
}

bool Tester::testDTreeBalanced(DTree& dtree, int numInsertions){
    for(int i = 0; i < numInsertions; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }

    bool returnStatus = true;

    testDTreeBalancedHelper(dtree, dtree._root, returnStatus);

    return returnStatus;
}

void Tester::testDTreeBalancedHelper(DTree& dtree, DNode* node, bool& returnStatus){

    if(dtree.checkImbalance(node)){
        cout << "Imbalance at node " << node->getDiscriminator() << endl;
        if(node->_left != nullptr){
            cout << "Left size: " << node->_left->_size;
        }else{
            cout << "Left size: 0" << endl;
        }

        if(node->_right != nullptr){
            cout << "Right size: " << node->_right->_size;
        }else{
            cout << "Right size: 0" << endl;
        }

        returnStatus = false;
    }

    if(node->_left != nullptr){
        testDTreeBalancedHelper(dtree, node->_left, returnStatus);
    }

    if(node->_right != nullptr){
        testDTreeBalancedHelper(dtree, node->_right, returnStatus);
    }


}

// Insert 10 random nodes and delete 2 random nodes until size of tree is 9999
// The idea of this test is this should never crash
// If it does it has located some type of edge case
// void Tester::DTreeShotgunTest(DTree& dtree, int insertSize, int deleteSize, int totalSize){
//     dtree.clear();

//     int numInsertions = 0;
//     int numDuplicateInsertions = 0;
//     int numDeletions = 0;
//     int numDuplicateDeletions = 0;


//     while(dtree.getTreeSize() < insertSize){
//         int disc = RANDDISC;
//         Account newAcct;

//         for(int i = 0; i < numInsertions; ++i){
//             disc = RANDDISC;
//             newAcct = Account("", disc, 0, "", "");
//             // cout << dtree.insert(newAcct) << endl;
//             while(!dtree.insert(newAcct)){
//                 // cout << "here" << endl;
//                 disc = RANDDISC;
//                 newAcct = Account("", disc, 0, "", "");
//                 numDuplicateInsertions++;
//             }
//             numInsertions++;
//         }
        
//         TreeArray* treeArr;
//         int del_disc;

//         for(int i = 0; i < deleteSize; ++i){
//             if(dtree._root->_numVacant != dtree.getTreeSize()){
//                 treeArr = dtree.treeToArray(dtree._root);
//                 std::uniform_int_distribution<> distr(0, treeArr->size-1);
//                 int index = distr(rng);

//                 del_disc = treeArr->array[index].getDiscriminator();

//                 DNode* node;
//                 while(!dtree.remove(del_disc, node)){
//                     cout << "here" << endl;
//                     index = distr(rng);
//                     del_disc = treeArr->array[index].getDiscriminator();
//                     numDuplicateDeletions++;
//                 }
//                 numDeletions++;

//                 delete treeArr;
//             }
//         }
//     }

//     cout << "Finished" << endl;
//     cout << "Num Insertions: " << numInsertions << endl;
//     cout << "Num Duplicate Insertions: " << numDuplicateInsertions << endl;
//     cout << "Num Deletions: " << numDeletions << endl;
//     cout << "Num Duplicate Deletions: " << numDuplicateDeletions << endl;

//     // dtree.dump();
//     // cout << endl;

// }


int main() {
    Tester tester;

    /* Basic dtree tests */
    DTree dtree;

    cout << "Testing DTree insertion..." << endl;
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

    cout << "\n\nTesting DTree clear..." << endl;
    if(tester.testDTreeClear(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree insert into empty tree..." << endl;
    if(tester.testDTreeInsertIntoEmptyTree(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree remove node that doesn't exist..." << endl;
    if(tester.testDTreeRemoveNonExistentNode(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree remove vacant node..." << endl;
    if(tester.testDTreeRemoveVacantNode(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }


    cout << "\n\nTesting DTree tree to array..." << endl;
    tester.testDTreeTreeToArray(dtree);

    cout << "\n\nTesting DTree deep copy..." << endl;
    if(tester.testDTreeDeepCopy(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree search..." << endl;
    if(tester.testDTreeSearch(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced w/ 5 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 5)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced w/ 15 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 15)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced w/ 50 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 50)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }


    cout << "\n\nTesting DTree balanced w/ 100 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 100)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    // cout << "\n\nShotgun test..." << endl;
    // tester.DTreeShotgunTest(dtree, 10, 2, 8000);

    cout << "\n\nTesting DTree balanced w/ 500 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 500)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }


    return 0;
}

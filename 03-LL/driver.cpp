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
    bool testDTreeDuplicateInsert(DTree& dtree);
    bool testDTreeInsertIntoVacantNode(DTree& dtree);
    
    bool testDTreeRemoveNonExistentNode(DTree& dtree);
    bool testDTreeRemoveVacantNode(DTree& dtree);

    void testDTreeTreeToArray(DTree& dtree);

    bool testDTreeDeepCopy(DTree& dtree);

    bool testDTreeSearch(DTree& dtree);

    bool testDTreeBalanced(DTree& dtree, int numInsertions);
    void testDTreeBalancedHelper(DTree& dtree, DNode* node, bool& returnStatus);
    bool testDTreeBalancedLeftOnlyInsert(DTree& dtree, int numInsertions);
    bool testDTreeBalancedRightOnlyInsert(DTree& dtree, int numInsertions);
    bool testDTreeBalancedAllNodesRemoved(DTree& dtree);

    bool testDTreeBSTProperty(DTree& dtree, int numInsertions);
    void testDTreeBSTPropertyHelper(DNode* node, bool& returnStatus);


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
    int numDiscriminators = 5;
    int discriminators[] = {207, 251, 883, 1503, 1691};
    DNode* removed = nullptr;

    for(int i = 0; i < numDiscriminators; i++) {
        if(!dtree.remove(discriminators[i], removed)) {
            cout << "Deletion on node " << discriminators[i] << " did not return true" << endl;
            allRemoved = false;
        }
    }

    cout << "Dumping the tree after 5 deletions: " << endl;
    dtree.dump();
    cout << endl;

    cout << "Inserting 7 elements to cause an imbalance and to clear vacant nodes: " << endl;
    
    int numInsert = 7;
    Account bigAcct = Account("", 9999, 0, "", "");
    for(int i = 0; i < numInsert; ++i){
        bigAcct = Account("", 9999-i, 0, "", "");
        dtree.insert(bigAcct);
    }

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

bool Tester::testDTreeInsertIntoVacantNode(DTree& dtree){
    dtree.clear();

    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct); 
    }


    Account newAcct = Account("", 9999, 0, "", "");
    dtree.insert(newAcct);

    DNode* node;
    dtree.remove(9999, node);
    if(dtree.insert(newAcct)) return true;
    return false;
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
    dtree.clear();

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

bool Tester::testDTreeBalancedLeftOnlyInsert(DTree& dtree, int numInsertions){
    dtree.clear();

    for(int i = 0; i < numInsertions; i++) {
        Account newAcct = Account("", 9999-i, 0, "", "");
        dtree.insert(newAcct);
    }

    cout << "Tree dump: " << endl;
    dtree.dump();
    cout << endl;

    bool returnStatus = true;

    testDTreeBalancedHelper(dtree, dtree._root, returnStatus);

    return returnStatus;

}


bool Tester::testDTreeBalancedRightOnlyInsert(DTree& dtree, int numInsertions){
    dtree.clear();

    for(int i = 0; i < numInsertions; i++) {
        Account newAcct = Account("", i, 0, "", "");
        dtree.insert(newAcct);
    }

    cout << "Tree dump: " << endl;
    dtree.dump();
    cout << endl;

    bool returnStatus = true;

    testDTreeBalancedHelper(dtree, dtree._root, returnStatus);

    return returnStatus;

}


bool Tester::testDTreeBalancedAllNodesRemoved(DTree& dtree){
    dtree.clear();

    // Insert root node
    Account newAcct = Account("", 10, 0, "", "");
    dtree.insert(newAcct);


    // Insert 3 nodes on the left side
    newAcct = Account("", 9, 0, "", "");
    dtree.insert(newAcct);

    newAcct = Account("", 8, 0, "", "");
    dtree.insert(newAcct);

    newAcct = Account("", 7, 0, "", "");
    dtree.insert(newAcct);

    // Remove all three nodes & root node (mark vacant)
    DNode* node;
    dtree.remove(10, node);
    dtree.remove(9, node);
    dtree.remove(8, node);
    dtree.remove(7, node);

    cout << "Tree dump after deletion: " << endl;
    dtree.dump();
    cout << endl;

    // Insert one more node on the left side to create imbalance and clear vacant nodes
    newAcct = Account("", 2, 0, "", "");
    dtree.insert(newAcct);


    cout << "Tree dump after rebalance: " << endl;
    dtree.dump();
    cout << endl;

    if(dtree._root->getDiscriminator() != 2) return false;

    return true;
    
}

bool Tester::testDTreeBSTProperty(DTree& dtree, int numInsertions){
    dtree.clear();

    for(int i = 0; i < numInsertions; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }

    bool returnStatus = true;

    testDTreeBSTPropertyHelper(dtree._root, returnStatus);

    return returnStatus;
}

void Tester::testDTreeBSTPropertyHelper(DNode* node, bool& returnStatus){
    if(node->_left != nullptr){
        if(node->_left->getDiscriminator() < node->getDiscriminator()){
            testDTreeBSTPropertyHelper(node->_left, returnStatus);
        }else{
            returnStatus = false;
        }
    
    }

    if(node->_right != nullptr){
        if(node->_right->getDiscriminator() > node->getDiscriminator()){
            testDTreeBSTPropertyHelper(node->_right, returnStatus);
        }else{
            returnStatus = false;
        }
    }
}

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

    cout << "\n\nTesting DTree insert into vacant node..." << endl;
    if(tester.testDTreeInsertIntoVacantNode(dtree)) {
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

    cout << "\n\nTesting DTree balanced w/ 500 insertions..." << endl;
    if(tester.testDTreeBalanced(dtree, 500)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced(left insert only) w/ 20 insertions..." << endl;
    if(tester.testDTreeBalancedLeftOnlyInsert(dtree, 20)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced(right insert only) w/ 20 insertions..." << endl;
    if(tester.testDTreeBalancedRightOnlyInsert(dtree, 20)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree balanced(all nodes removed)" << endl;
    if(tester.testDTreeBalancedAllNodesRemoved(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting DTree BST property w/ 500 insertions..." << endl;
    if(tester.testDTreeBSTProperty(dtree, 500)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    return 0;
}

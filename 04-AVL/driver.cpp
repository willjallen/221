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
    // bool testBasicDTreeInsert(DTree& dtree);
    // bool testBasicDTreeRemove(DTree& dtree);

    bool testUTreeInsertSameUsername(UTree& utree);
    bool testBaiscUTreeRemove(UTree& utree);

    void UTreeLoadDataOnlyUsernames(UTree& utree);
    void UTreeLoadData(UTree& utree);


    bool testUTreeClear(UTree& utree);

    bool testUTreeInsertIntoEmptyTree(UTree& utree);
    bool testUTreeDuplicateInsert(UTree& utree);
    bool testUTreeInsertIntoVacantNode(UTree& utree);

    bool testUTreeInsertLeftRotation(UTree& utree);
    bool testUTreeInsertRightRotation(UTree& utree);

    bool testUTreeInsertLeftRightRotation(UTree& utree);
    bool testUTreeInsertRightLeftRotation(UTree& utree);
    
    bool testUTreeLoadData(UTree& utree);

    bool testUTreeRemoveNonExistentNode(UTree& utree);
    bool testUTreeRemoveVacantTreeNode(UTree& utree);

    bool testUTreeRemoveAccount(UTree& utree);

    bool testUTreeRemoveAVLNodeLeaf(UTree& utree);
    bool testUTreeRemoveAVLNodeLeftSubtreeWithChild(UTree& utree);
    bool testUTreeRemoveAVLNodeLeftSubtreeWithNoChild(UTree& utree);
    bool testUTreeRemoveAVLNodeRightSubtree(UTree& utree);


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

bool Tester::testUTreeInsertSameUsername(UTree& utree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = i;
        Account newAcct = Account("cool", disc, 0, "", "");
        if(!utree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    cout << "Resulting DTree:" << endl;
    utree.dump();
    cout << endl;
    return allInserted;
}

bool Tester::testUTreeDuplicateInsert(UTree& utree){
    utree.clear();

    Account newAcct = Account("nice", 1111, 0, "", "");
    utree.insert(newAcct);
    return !(utree.insert(newAcct));
}

void Tester::UTreeLoadDataOnlyUsernames(UTree& utree){
    utree.clear();
    string* usernames = new string[8]{"Aqua5Seemly", "Brackle", "Capstan", "Cinnamon", "Pika", "Sulkyreal", "Allegator", "Kippage"};
    Account newAcct = Account("", 0, 0, "", "");

    for(int i = 0; i < 8; i++){
        newAcct = Account(usernames[i], 0, 0 ,"","");
        utree.insert(newAcct);
    }

    delete[] usernames;
}

void Tester::UTreeLoadData(UTree& utree){
    utree.clear();
    utree.loadData("accounts.csv", false);
}

bool Tester::testUTreeLoadData(UTree& utree){
    utree.clear();
    utree.loadData("accounts.csv", false);

    string expectedVal = "((((Allegator:0:16)Aqua5Seemly:1:22)Brackle:2:41(Capstan:0:18))Cinnamon:3:48((Kippage:0:22)Pika:1:25(Sulkyreal:0:8)))";

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;

    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeInsertLeftRotation(UTree& utree){
    
    utree.clear();

    string expectedVal = "((3:0:1)5:1:1(7:0:1))";

    Account newAcct = Account("3", 0, 0, "", "");
    utree.insert(newAcct);
    newAcct = Account("5", 1, 0 ,"","");
    utree.insert(newAcct);
    newAcct = Account("7", 2, 0 ,"","");
    utree.insert(newAcct);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;


    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeInsertRightRotation(UTree& utree){
    
    utree.clear();

    string expectedVal = "((2:0:1)3:1:1(5:0:1))";

    Account newAcct = Account("5", 0, 0, "", "");
    utree.insert(newAcct);
    newAcct = Account("3", 1, 0 ,"","");
    utree.insert(newAcct);
    newAcct = Account("2", 2, 0 ,"","");
    utree.insert(newAcct);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;


    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeInsertLeftRightRotation(UTree& utree){
    utree.clear();

    string expectedVal = "((3:0:1)4:1:1(5:0:1))";

    Account newAcct = Account("5", 0, 0, "", "");
    utree.insert(newAcct);
    newAcct = Account("3", 1, 0 ,"","");
    utree.insert(newAcct);
    newAcct = Account("4", 2, 0 ,"","");
    utree.insert(newAcct);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;


    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeInsertRightLeftRotation(UTree& utree){
    utree.clear();

    string expectedVal = "((3:0:1)4:1:1(5:0:1))";

    Account newAcct = Account("3", 0, 0, "", "");
    utree.insert(newAcct);
    newAcct = Account("5", 1, 0 ,"","");
    utree.insert(newAcct);
    newAcct = Account("4", 2, 0 ,"","");
    utree.insert(newAcct);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;


    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeClear(UTree& utree){
    UTreeLoadData(utree);
    utree.clear();

    if(utree._root != nullptr){
        return false;
    }

    return true;
}





bool Tester::testUTreeRemoveNonExistentNode(UTree& utree){
    bool status = true;

    utree.clear();
    Account newAcct = Account("hi", 0, 0, "", "");
    if(!utree.insert(newAcct)) status = false;

    newAcct = Account("hi", 1, 0, "", "");
    if(!utree.insert(newAcct)) status = false;

    newAcct = Account("kush", 69, 0, "", "");
    if(!utree.insert(newAcct)) status = false;
    
    DNode* node;
    if(utree.removeUser("poopoo", 3, node) != false) status = false;

    if(utree.removeUser("hi", 2, node) != false) status = false;

    if(utree.removeUser("kush", 70, node) != false) status = false;


    return status;
}

bool Tester::testUTreeRemoveAccount(UTree& utree){
    utree.clear();
    
    string expectedVal = "((((Allegator:0:14)Aqua5Seemly:1:19)Brackle:2:41(Capstan:0:17))Cinnamon:3:47((Kippage:0:22)Pika:1:25(Sulkyreal:0:8)))";
    
    UTreeLoadData(utree);

    DNode* removed = nullptr;
    utree.removeUser("Allegator", 8926, removed);
    utree.removeUser("Allegator", 6938, removed);

    utree.removeUser("Aqua5Seemly", 3922, removed);
    utree.removeUser("Aqua5Seemly", 7300, removed);
    utree.removeUser("Aqua5Seemly", 1309, removed);

    utree.removeUser("Capstan", 604, removed);

    utree.removeUser("Cinnamon", 7713, removed);

    utree.removeUser("Brackle", 999, removed); // No disc

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;

    if(buffer.str() == expectedVal) return true;
    return false;
}

bool Tester::testUTreeRemoveAVLNodeLeaf(UTree& utree){
    utree.clear();
    
    string expectedVal = "(((Aqua5Seemly:0:1)Brackle:1:1(Capstan:0:1))Cinnamon:2:1((Kippage:0:1)Pika:1:1(Sulkyreal:0:1)))";
    
    UTreeLoadDataOnlyUsernames(utree);

    DNode* removed = nullptr;
    utree.removeUser("Allegator", 0, removed);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;

    if(buffer.str() == expectedVal) return true;
    return false;    
}

bool Tester::testUTreeRemoveAVLNodeLeftSubtreeWithChild(UTree& utree){
    utree.clear();
    
    string expectedVal = "(((Allegator:0:1)Aqua5Seemly:1:1(Capstan:0:1))Cinnamon:2:1((Kippage:0:1)Pika:1:1(Sulkyreal:0:1)))";
    
    UTreeLoadDataOnlyUsernames(utree);

    DNode* removed = nullptr;
    utree.removeUser("Brackle", 0, removed);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;

    if(buffer.str() == expectedVal) return true;
    return false;    
}

bool Tester::testUTreeRemoveAVLNodeLeftSubtreeWithNoChild(UTree& utree){
    utree.clear();
    
    string expectedVal = "((((Allegator:0:1)Aqua5Seemly:1:1)Brackle:2:1(Capstan:0:1))Cinnamon:3:1(Kippage:1:1(Sulkyreal:0:1)))";
    
    UTreeLoadDataOnlyUsernames(utree);

    DNode* removed = nullptr;
    utree.removeUser("Pika", 0, removed);

    cout << "Expected:" << endl;
    cout << expectedVal << endl;
    cout << "Result:" << endl;

    std::stringstream buffer;
    utree.dumpToString(buffer);
    cout << buffer.str() << endl;

    if(buffer.str() == expectedVal) return true;
    return false;    
}


int main() {
    Tester tester;

    /* Basic dtree tests */
    // DTree dtree;
    UTree utree;

    /* === Insertion Stuff === */
    // {
    //     cout << "Testing UTree insertion w/ same username..." << endl;
    //     if(tester.testUTreeInsertSameUsername(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree insertion into empty tree..." << endl;
    //     if(tester.testUTreeInsertIntoEmptyTree(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree duplicate insertion..." << endl;
    //     if(tester.testUTreeDuplicateInsert(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree left rotation..." << endl;
    //     if(tester.testUTreeInsertLeftRotation(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree right rotation..." << endl;
    //     if(tester.testUTreeInsertRightRotation(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree left right rotation..." << endl;
    //     if(tester.testUTreeInsertLeftRightRotation(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree right left rotation..." << endl;
    //     if(tester.testUTreeInsertRightLeftRotation(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }

    //     cout << "\n\nTesting UTree load data..." << endl;
    //     if(tester.testUTreeLoadData(utree)) {
    //         cout << "test passed" << endl;
    //     } else {
    //         cout << "test failed" << endl;
    //     }
    // }

    /* === Deletion Stuff === */

    // cout << "\n\nTesting UTree remove account..." << endl;
    // if(tester.testUTreeRemoveAccount(utree)) {
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


    // cout << "\n\nTesting UTree remove non existent nodes..." << endl;
    // if(tester.testUTreeRemoveNonExistentNode(utree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    // cout << "\n\nTesting UTree remove AVL leaf node..." << endl;
    // if(tester.testUTreeRemoveAVLNodeLeaf(utree)) {
    //     cout << "test passed" << endl;
    // } else {
    //     cout << "test failed" << endl;
    // }

    cout << "\n\nTesting UTree remove AVL node w/ left subtree & child..." << endl;
    if(tester.testUTreeRemoveAVLNodeLeftSubtreeWithChild(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "\n\nTesting UTree remove AVL node w/ left subtree & no child..." << endl;
    if(tester.testUTreeRemoveAVLNodeLeftSubtreeWithNoChild(utree)) {
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








    return 0;
}

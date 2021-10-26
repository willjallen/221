#include "dtree.h"
#include <random>

#define NUMACCTS 10
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);
    void testTreeToArray(DTree& dtree);

};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        
        bool rtrn = dtree.insert(newAcct);
        std::cout << (rtrn ? "true" : "false") << std::endl;
        std::cout << rtrn << std::endl;
        if(!rtrn) {
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

void Tester::testTreeToArray(DTree& dtree){
    TreeArray* treeArr = dtree.treeToArray(dtree._root);
    for(int i = 0; i < treeArr->size; ++i){
        cout << treeArr->array[i].getDiscriminator() << ", ";
    }
    cout << endl;
    delete treeArr;
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

    // cout << "To Array" << endl;
    // tester.testTreeToArray(dtree);


    return 0;
}

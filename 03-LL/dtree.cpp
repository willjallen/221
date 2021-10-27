/**
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */


#include "dtree.h"


/**
 * Destructor, deletes all dynamic memory.
 */
DTree::~DTree() {
    clear();
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {
    _root = copy(rhs._root);
    return *this;
}

DNode* DTree::copy(const DNode* rhsNode){
    if(rhsNode == nullptr) return nullptr;

    DNode* newNode = new DNode(rhsNode->getAccount());
    newNode->_left = copy(rhsNode->_left);
    newNode->_right = copy(rhsNode->_right);
    return newNode;
}

/**
 * Dynamically allocates a new DNode in the tree. 
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {


    if(_root == nullptr){
        _root = new DNode(newAcct);
        return true;
    }else{
        bool rtrn =  recursiveInsert(_root, newAcct);
        updateAndRebalanceAlongPath(newAcct.getDiscriminator());
        return rtrn;
    }





}


/**
 * Recursive implementation of insert
 * @param node the root node to begin insertion from
 * @param newAcct the account to add
 */ 
bool DTree::recursiveInsert(DNode* node, Account newAcct){

    // Update size of node and numVacant
    
    cout << "Current Node: " << node->getDiscriminator() << std::endl;
    cout << "New account to add: " << newAcct.getDiscriminator() << std::endl;
    cout << endl;

    int nodeDisc = node->getDiscriminator();

    if(newAcct.getDiscriminator() < nodeDisc){
        // Does the node exist?
        if(node->_left != nullptr){
            // Is it vacant?
            if(node->_left->_vacant){
                // Is it unique?
                if(!retrieve(nodeDisc)){
                    // Fill Vacant node
                    node->_left->_vacant = false;
                    return true;

                }else{
                    // Duplicate
                    return false;
                }
            }else{
                // Continue searching
                return recursiveInsert(node->_left, newAcct);

            }
        }else{
        // Create a new node

            node->_left = new DNode(newAcct);
            return true;

        }

    }



    else if(newAcct.getDiscriminator() > nodeDisc){
        // Does the node exist?
        if(node->_right != nullptr){
            // Is it vacant?
            if(node->_right->_vacant){
                // Is it unique?
                if(!retrieve(nodeDisc)){
                    // Fill Vacant node
                    node->_right->_vacant = false;

                    return true;

                }else{
                    // Duplicate
                    return false;
                }

            }else{
                // Continue searching
                return recursiveInsert(node->_right, newAcct);
            }
        }else{
        // Create a new node
            
            node->_right = new DNode(newAcct);           
            return true;


        }

    }else{
        std::cout << "Found Duplicate" << std::endl;
        return false;
    }
    




}


/**
 * Updates the sizes and number of vacant nodes along the path to a trajectory node
 * Also checks for a size imbalance between two child nodes, and calls rebalance if so
 * @param node the target node
 * @return true if target node was found
 */
bool DTree::updateAndRebalanceAlongPath(int disc){
    if(retrieve(disc)){
        recursiveUpdateAndRebalanceAlongPath(_root, disc);
        return true;
    }

    return false;
}


/**
 * Recursive implementation of updateAndRebalanceAlongPath
 * This works by updating on the unwinding trajectory of the stack
 * @param node the root node
 * @param disc the target node
 */
void DTree::recursiveUpdateAndRebalanceAlongPath(DNode* node, int disc){
    int nodeDisc = node->getDiscriminator();

    if(disc < nodeDisc){
        recursiveUpdateAndRebalanceAlongPath(node->_left, disc);
    }

    if(disc > nodeDisc){
        recursiveUpdateAndRebalanceAlongPath(node->_right, disc);
    }

    std::cout << "Rebalancing disc:" << nodeDisc << std::endl;
    updateAndRebalanceNode(node);
    return;

}


/**
 * Updates the sizes and number of vacant nodes along the path to a trajectory node
 * @param disc the target node
 * @return true if target node was found
 */
bool DTree::updateAlongPath(int disc){
    if(retrieve(disc)){
        recursiveUpdateAlongPath(_root, disc);
        return true;
    }

    return false;
}   

/**
 * Recursive implementation of updateAlongPath
 * @param node the root node
 * @param disc the target node
 */
void DTree::recursiveUpdateAlongPath(DNode* node, int disc){
    int nodeDisc = node->getDiscriminator();

    if(disc < nodeDisc){
        recursiveUpdateAlongPath(node->_left, disc);
    }

    if(disc > nodeDisc){
        recursiveUpdateAlongPath(node->_right, disc);
    }

    std::cout << "disc:" << nodeDisc << std::endl;
    updateNode(node);
    return;

}



/**
 * Updates the size and number of vacant nodes of a specific node
 * Also checks for a size imbalance between two child nodes, and calls rebalance if so
 * @param node the target node
 */
void DTree::updateAndRebalanceNode(DNode* node){
    updateSize(node);
    updateNumVacant(node);
    if(checkImbalance(node)) rebalance(node);

}

/**
 * Updates the size and number of vacant nodes of a specific node
 * @param node the target node
 */
void DTree::updateNode(DNode* node){
    updateSize(node);
    updateNumVacant(node);

}


/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node) {
    int size = 1;
    if(node->_left != nullptr){
        size += node->_left->_size;
    }

    if(node->_right != nullptr){
        size += node->_right->_size;
    }

    node->_size = size;
}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {
    int numVacant = 0;
    if(node->isVacant()){
        numVacant = 1;
    }

    if(node->_left != nullptr){
        numVacant += node->_left->_numVacant;
    }

    if(node->_right != nullptr){
        numVacant += node->_right->_numVacant;
    }

    node->_numVacant = numVacant;
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node) {
    bool imbalance = false;

    if(node->_left != nullptr && node->_right != nullptr){

        if(node->_left->_size < 4 && node->_right->_size < 4){
            return false;
        }

        if(node->_left->_size * 1.5 < node->_right->_size || node->_right->_size * 1.5 < node->_left->_size){
            cout << "Imbalance found" << endl;
            cout << "Left Node Size: "  << node->_left->_size << endl;
            cout << "Right Node Size: "  << node->_right->_size << endl;
            return true;
        }
    }

    return false;


}


/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed) {
    bool status = recursiveRemove(_root, disc, removed);
    updateAndRebalanceAlongPath(disc);
    return status;
 }


/**
 * Recursive implementation of remove
 * @param node the root node
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::recursiveRemove(DNode* node, int disc, DNode*& removed){
    if(node == nullptr) return false;

    int nodeDisc = node->getDiscriminator();

    if(disc < nodeDisc){
        return recursiveRemove(node->_left, disc, removed);
    }

    else if(disc > nodeDisc){
        return recursiveRemove(node->_right, disc, removed);
    }
    else{
        
        if(!node->isVacant()){
            
            removed = node;

            node->_vacant = true;
            return true;
        }else{
            return false;
        }

        
    }

    return false;


 }

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc) {
    if(_root != nullptr){
        
        if(_root->getDiscriminator() == disc){
            return _root;
        }

        return recursiveSearch(_root, disc);
    }

    return nullptr;
}

/**
 * Recursively searches the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::recursiveSearch(DNode* node, int disc){
    if(node == nullptr) return nullptr;

    int nodeDisc = node->getDiscriminator();

    if(disc < nodeDisc){
        return recursiveSearch(node->_left, disc);
    }


    if(disc > nodeDisc){
        return recursiveSearch(node->_right, disc);
    }

    return node;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {
    recursiveClear(_root);
}

/**
 * Recursively clears the tree
 * @param node the root node
 */
void DTree::recursiveClear(DNode* node){
    if(node == nullptr) return;
    recursiveClear(node->_left);
    recursiveClear(node->_right);
    cout << "Deleting: " << node->getDiscriminator() << endl;
    delete node;
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {
    recursivePrintAccounts(_root);
}

/**
 * Recursively prints the accounts in the tree (inorder traversal)
 * @param node the root node
 */
void DTree::recursivePrintAccounts(DNode* node) const {
    if(node == nullptr) return;

    recursivePrintAccounts(node->_left);
    cout << node->getAccount() << endl;
    recursivePrintAccounts(node->_right);
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
    return _root->getSize();
}

/**
 * Allocates a new array of nodes, excluding vacant nodes, sorted in increasing order
 * @param node the root node
 * @return pointer to TreeArray struct
 */ 
TreeArray* DTree::treeToArray(DNode* node){
    int totalSize = 1 + (node->_left->_size - node->_left->_numVacant) + (node->_right->_size - node->_right->_numVacant);
    TreeArray* treeArr = new TreeArray(totalSize);

    int itr = 0;
    recursiveTreeToArray(node, treeArr->array, itr);

    return treeArr;
}

/**
 * Recursive implementation of treeToArray (inorder traversal)
 * @param node the root node
 * @param arr array of nodes to fill
 * @param itr iteration variable
 */ 
void DTree::recursiveTreeToArray(DNode* node, DNode* arr, int& itr){
    if(node == nullptr) return;

    recursiveTreeToArray(node->_left, arr, itr);

    if(!node->isVacant()){
        arr[itr] = DNode(node->getAccount());
        itr += 1;
    }

    recursiveTreeToArray(node->_right, arr, itr);
}




/**
 * Constructs a (close to) perfect BST given an array of nodes
 * @param node the root node
 * @param treeArray* pointer to TreeArray struct
 */ 
void DTree::arrayToTree(DNode* node, TreeArray* treeArr){
    recursiveBisectArrayIntoTree(node, treeArr->array, subArrIndxs(0, treeArr->size-1), true);
}

/**
 * Recursive implementation of arrayToTree
 * Constructs a (close to) perfect BST by means of recursive array bisection (preorder traversal)
 * Even indices are biased left
 * @param node the root node
 * @param treeArray* pointer to TreeArray struct
 */ 




void DTree::recursiveBisectArrayIntoTree(DNode* rootInsertNode, DNode* nodeArray, subArrIndxs bisectedArr, bool firstPass){
    int size = (bisectedArr._right - bisectedArr._left) + 1; 
    if(size <= 0 || bisectedArr._left > bisectedArr._right) return;

    int rootNodeIndex = bisectedArr._left + (size-1)/2;
    // Visit
    if(firstPass){
        rootInsertNode->_account = nodeArray[rootNodeIndex].getAccount();
        cout << "Setting rootNode to: " << nodeArray[rootNodeIndex].getAccount().getDiscriminator() << endl;

    }else{
        cout << "Inserting: " << nodeArray[rootNodeIndex].getAccount().getDiscriminator() << endl;
        recursiveInsert(rootInsertNode, nodeArray[rootNodeIndex].getAccount());
        updateAlongPath(nodeArray[rootNodeIndex].getAccount().getDiscriminator());
    }
    // Left
    recursiveBisectArrayIntoTree(rootInsertNode, nodeArray, subArrIndxs(bisectedArr._left, rootNodeIndex-1), false);
    // Right
    recursiveBisectArrayIntoTree(rootInsertNode, nodeArray, subArrIndxs(rootNodeIndex+1, bisectedArr._right), false);
}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
void DTree::rebalance(DNode*& node) {
    cout << "===================" << endl;
    cout << "Rebalance: " << node->getDiscriminator() << endl;
    
    cout << "Tree before clear:" << endl;
    dump();
    cout << endl;

    TreeArray* treeArr = treeToArray(node);
    cout << "TreeArr: " << endl;
    cout << "size=" << treeArr->size << endl;
    for(int i = 0; i < treeArr->size; ++i){
        cout << treeArr->array[i].getDiscriminator() << ", ";
    }
    cout << endl;

    // Clear and reset the root node
    // Don't delete as other nodes might connect to it

    recursiveClear(node->_left);
    node->_left = nullptr;
    recursiveClear(node->_right);
    node->_right = nullptr;
    node->_size = 1;
    cout << "Tree after clear:" << endl;
    
    dump();
    cout << endl;

    arrayToTree(node, treeArr);
    cout << "Tree after arrayToTree:" << endl;
    dump();
    cout << endl;
    cout << "====================" << endl;
    delete treeArr;
}

// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
// DNode* DTree::rebalance(DNode* node) {



//     return nullptr;
// }
// ----------------

/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() << 
            "\n\tDiscriminator: " << acct.getDiscriminator() <<
            "\n\tNitro: " << acct.hasNitro() << 
            "\n\tBadge: " << acct.getBadge() << 
            "\n\tStatus: " << acct.getStatus();
    return sout;
}
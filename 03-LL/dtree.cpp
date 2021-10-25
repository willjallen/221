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
        std::cout << "retrieve: " << std::endl;
        std::cout << retrieve(newAcct.getDiscriminator()) << std::endl;
        updateAndRebanceAlongPath(newAcct.getDiscriminator());
        // std::cout << (rtrn ? "true" : "false") << std::endl;
        // std::cout << (!rtrn ? "true" : "false") << std::endl;
        return (int)rtrn;
    }





}


// Visit, left, right
bool DTree::recursiveInsert(DNode* node, Account newAcct){

    // Update size of node and numVacant
    

    cout << "node: " << node->getDiscriminator() << std::endl;
    cout << "new account: " << newAcct.getDiscriminator() << std::endl;

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
        std::cout << "duplicate" << std::endl;
        std::cout << std::endl;
        std::cout << "node: " << node->getDiscriminator() << std::endl;
        std::cout << "new account: " << newAcct.getDiscriminator() << std::endl;
        return false;
    }
    




}


/**
 * Bootstrap
 * Updates the sizes and number of vacant nodes along the path to a trajectory node
 * @param node the target node
 * @return true if target node was found
 */
bool DTree::updateAndRebanceAlongPath(int disc){
    if(retrieve(disc)){
        recursiveUpdateAndRebanceAlongPath(_root, disc);
        return true;
    }

    return false;
}


/**
 * Updates the sizes and number of vacant nodes along the path to a trajectory node
 * This works by updating on the unwiding trajectory of the stack
 * @param node the target node
 * 
 */
void DTree::recursiveUpdateAndRebanceAlongPath(DNode* node, int disc){
    int nodeDisc = node->getDiscriminator();

    if(disc < nodeDisc){
        recursiveUpdateAndRebanceAlongPath(node->_left, disc);
    }

    if(disc > nodeDisc){
        recursiveUpdateAndRebanceAlongPath(node->_right, disc);
    }

    std::cout << "disc:" << nodeDisc << std::endl;
    updateAndRebalanceNode(node);
    return;

}





/**
 * Updates the size and number of vacant nodes of a specific node
 * @param node the target node
 * 
 */
void DTree::updateAndRebalanceNode(DNode* node){
    updateSize(node);
    updateNumVacant(node);
    if(checkImbalance(node)) rebalance(node);

}


/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed) {
    bool status = recursiveRemove(_root, disc, removed);
    updateAndRebanceAlongPath(disc);
    return status;
 }

/*


TODO: return true/false does not propogate up the stack in the way i want updateAndReblance to
idk how to fix this

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

void DTree::recursiveClear(DNode* node){
    if(node == nullptr) return;
    recursiveClear(node->_left);
    recursiveClear(node->_right);
    delete node;
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {

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
    }

    return false;


}


std::shared_ptr<TreeArray> DTree::treeToArray(DNode* node){
    int totalSize = 1 + (node->_left->_size - node->_left->_numVacant) + (node->_right->_size - node->_right->_numVacant);
    std::shared_ptr<TreeArray> treeArr = std::make_shared<TreeArray>(totalSize);

    int itr = 0;
    recursiveTreeToArray(node, treeArr->array, itr);

    return treeArr;
}

// Inorder: Left root right
void DTree::recursiveTreeToArray(DNode* node, DNode* arr, int& itr){
    if(node == nullptr) return;
    // TODO remove vacant
    recursiveTreeToArray(node->_left, arr, itr);
    if(!node->isVacant()){
        arr[itr] = DNode(node->getAccount());
        itr += 1;
    }
    recursiveTreeToArray(node->_right, arr, itr);
}





void DTree::arrayToTree(DNode* node, std::shared_ptr<TreeArray> arr){

    std::shared_ptr<TreeArray> treeArr = std::move(arr);

    std::shared_ptr<BisectedArray> bisectedArray = bisectArray(treeArr->array, treeArr->size);    

    recursiveArrayToTree(node, bisectedArray);



}

void DTree::recursiveArrayToTree(DNode* node, std::shared_ptr<BisectedArray> bArray){
    std::shared_ptr<BisectedArray> bisectedArray = std::move(bArray);

    // Visit, left, right
    recursiveInsert(node, bisectedArray->rootNode->getAccount());
    
    // Left
    // Root should be value of leftBisect
    recursiveArrayToTree(node, bisectArray(bisectedArray->leftArray, bisectedArray->leftArraySize));
    recursiveArrayToTree(node, bisectArray(bisectedArray->rightArray, bisectedArray->rightArraySize));
      
    


}

std::shared_ptr<BisectedArray> DTree::bisectArray(DNode* array, int size){

    int rootNodeIndex = (size-1)/2;

    int leftArraySize = rootNodeIndex;
    int rightArraySize = (size-1)-rootNodeIndex;

    DNode* leftArray = nullptr;
    DNode* rightArray = nullptr;
    DNode* rootNode = &(array[rootNodeIndex]);

    if(leftArraySize > 0){
        DNode* leftArray = new DNode[leftArraySize];
        for(int i = 0; i < leftArraySize; i++){
            leftArray[i] = array[i];
        }
    }

    if(rightArraySize > 0){
        DNode* rightArray = new DNode[rightArraySize];
        for(int i = 0; i < rightArraySize; i++){
            rightArray[i] = array[(rootNodeIndex+1)+i];
        }
    }


    return std::make_shared<BisectedArray>(leftArray, leftArraySize, rightArray, rightArraySize, rootNode); 
    return nullptr;

}



//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
void DTree::rebalance(DNode*& node) {
    std::shared_ptr<TreeArray> treeArr = treeToArray(node);
    arrayToTree(node, treeArr);
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
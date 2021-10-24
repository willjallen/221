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
                    // Update size of node and numVacant
                    updateAndRebalanceNode(node->_left);

                    return true;

                }else{
                    // Duplicate
                }
            }else{
                // Continue searching
                recursiveInsert(node->_left, newAcct);

                // Leave these methods on the stack for backwards traversal updating size
                updateAndRebalanceNode(node);


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
                    // Update size of node and numVacant
                    updateAndRebalanceNode(node->_right);

                    return true;

                }else{
                    // Duplicate
                }

            }else{
                // Continue searching
                recursiveInsert(node->_right, newAcct);

                // Leave these methods on the stack for backwards traversal updating size
                updateAndRebalanceNode(node);

            }
        }else{
        // Create a new node
            
            node->_right = new DNode(newAcct);
            return true;


        }

    }
    
    // Duplicate
    else{

        std::cout << "duplicate" << std::endl;
        std::cout << std::endl;
        std::cout << "node: " << node->getDiscriminator() << std::endl;
        std::cout << "new account: " << newAcct.getDiscriminator() << std::endl;
        return false;
    }



}


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
    DNode* node = retrieve(disc);
    removed = node;

    node->_vacant = true;

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
}

DNode* DTree::recursiveSearch(DNode* node, int disc){
    int nodeDisc = node->getDiscriminator();

    if(nodeDisc == disc){
        return node;
    }

    if(disc < nodeDisc){
        if(node->_left != nullptr){
            return recursiveSearch(node->_left, disc);
        }else{
            return nullptr;
        }
    }


    if(disc > nodeDisc){
        if(node->_right != nullptr){
            return recursiveSearch(node->_right, disc);
        }else{
            return nullptr;
        }
    }
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {

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

}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
// void DTree::rebalance(DNode*& node) {

// }

// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
DNode* DTree::rebalance(DNode* node) {
    
}
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
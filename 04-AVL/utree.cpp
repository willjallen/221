/**
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"
#include "dtree.h"

using std::cout;
using std::endl;

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
    clear();
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */ 
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while(std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes - 
         * Each line always has 5 sections of data */
        for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree. 
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct) {


    if(_root == nullptr){
        _root = new UNode();
        _root->getDTree()->insert(newAcct);
        return true;
    }

    if(recursiveInsert(_root, newAcct)){
        return true;
    }

    return false;

}


bool UTree::recursiveInsert(UNode* node, Account newAcct){
    if(newAcct.getUsername() < node->getUsername()){
        if(node->_left != nullptr){
            return recursiveInsert(node->_left, newAcct);
        }else{
            // Empty, insert new UNode
            UNode* newUNode = new UNode();
            node->_left = newUNode;
            // Add new account
            newUNode->getDTree()->insert(newAcct);
            updateAndRebalanceAlongPath(newAcct.getUsername());
            return true;
        }
    }

    if(newAcct.getUsername() > node->getUsername()){
        if(node->_right != nullptr){
            return recursiveInsert(node->_right, newAcct);
        }else{
            // Empty, insert
            UNode* newUNode = new UNode();
            node->_right = newUNode;
            // Add new account
            newUNode->getDTree()->insert(newAcct);
            updateAndRebalanceAlongPath(newAcct.getUsername());

            return true;
        }
    }

    if(node->getDTree()->insert(newAcct)){
        return true;
    }

    return false;
    





}

void UTree::updateAndRebalanceAlongPath(string username){

    recursiveUpdateAndRebalanceAlongPath(_root, username);

}

void UTree::recursiveUpdateAndRebalanceAlongPath(UNode* node, string username){
    if(node == nullptr) return;

    if(username < node->getUsername()){
        recursiveUpdateAndRebalanceAlongPath(node->_left, username);
    }
    if(username > node->getUsername()){
        recursiveUpdateAndRebalanceAlongPath(node->_right, username);
    }

    updateAndRebalance(node);


}

void UTree::updateAndRebalance(UNode* node){

    updateHeight(node);
    if(checkImbalance(node) == 1){
        rebalance(node);
    }
}

void UTree::updateAlongPath(string username){
    recursiveUpdateAlongPath(_root, username);
}

void UTree::recursiveUpdateAlongPath(UNode* node, string username){
    if(node == nullptr) return;


    if(username < node->getUsername()){
        recursiveUpdateAlongPath(node->_left, username);
    }
    if(username > node->getUsername()){
        recursiveUpdateAlongPath(node->_right, username);
    }

    updateHeight(node);
}




void UTree::retrieveParent(string username, UNode*& parent){
    recursiveRetrieveParent(_root, username, parent);
}

UNode* UTree::recursiveRetrieveParent(UNode* node, string username, UNode*& parent){
    if(node == nullptr){
        return nullptr;
    }


    if(username < node->getUsername()){
        parent = node;
        return recursiveRetrieveParent(node->_left, username, parent);
    }
    if(username > node->getUsername()){
        parent = node;
        return recursiveRetrieveParent(node->_right, username, parent);
    }

    return node;
}


/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {

    UNode* userNode = retrieve(username);

    if(!userNode){
        return false;
    }

    DNode* discNode = nullptr;
    userNode->getDTree()->remove(disc, discNode);

    if(!discNode){
        return false;
    }

    // DTree is empty?
    if(userNode->getDTree()->getNumUsers() == 0){
        // Delete the UNode
        removeAVLNode(userNode);
    }


    return true;

}


void UTree::removeAVLNode(UNode* node){
    /*
    1. If the node to delete has a left subtree, locate the largest node in the left subtree. 
     This node will be referenced as node X moving forward. Node X can be found by traversing down
     to the left once and then as far right as possible. Copy node X’s value (DTree) into the node
     with the empty DTree. (Hint: you overloaded an operator to perform to help here).

    2. If node X has a left child, the child will take node X’s place.

    3. Delete node X and, if it exists, shift the left child into its spot. 
    This can also be done by copying node X’s child’s value into node X and deleting the child
    instead.

    4. On the way back up the path taken to find node X, check for imbalances. AHH HOW

    5.If the node with an empty DTree does not have a left subtree, shift its right child into
    its spot.
    */
    UNode* leftNode = node->_left;
    UNode* rightNode = node->_right;

    // Is node a leaf?
    if(!leftNode && !rightNode){
        // Find parent
        UNode* parent = nullptr;
        retrieveParent(node->getUsername(), parent);
        
        // Nullify
        if(node->getUsername() < parent->getUsername()){
            parent->_left = nullptr;
        }

        if(node->getUsername() > parent->getUsername()){
            parent->_right = nullptr;
        }
        
        // Delete node
        delete node;


    
        // Traverse and update
        updateAndRebalanceAlongPath(parent->getUsername());

    }

    // Does node have a left subtree
    if(leftNode){

        // Find largest node in left subtree & capture parent
        UNode* parentToLargestNodeInLeftSubtree = node;
        UNode* largestNodeInLeftSubtree = findLargestNode(leftNode, parentToLargestNodeInLeftSubtree);
        
        UNode* leftChildOfLargestNodeInLeftSubtree = largestNodeInLeftSubtree->_left;

        // If largest node has a left child
        if(leftChildOfLargestNodeInLeftSubtree){

             // Swap largest node in left subtree w/ node
            *(node->getDTree()) = *(largestNodeInLeftSubtree->getDTree());

            // Copy left child into largest value
            *(largestNodeInLeftSubtree->getDTree()) = *(leftChildOfLargestNodeInLeftSubtree->getDTree());

            // Nullify
            largestNodeInLeftSubtree->_left = nullptr;
            
            // Delete the largest node
            delete leftChildOfLargestNodeInLeftSubtree;


            // Traverse and update
            updateAndRebalanceAlongPath(largestNodeInLeftSubtree->getUsername());

        }else{
            // If largest node does not have left child (we know it doesn't have a right child since it is the largest)

            // Nullify
            if(largestNodeInLeftSubtree->getUsername() < parentToLargestNodeInLeftSubtree->getUsername()){
                parentToLargestNodeInLeftSubtree->_left = nullptr;
            }

            if(largestNodeInLeftSubtree->getUsername() > parentToLargestNodeInLeftSubtree->getUsername()){
                parentToLargestNodeInLeftSubtree->_right = nullptr;
            }
            

            *(node->getDTree()) = *(largestNodeInLeftSubtree->getDTree());

            delete largestNodeInLeftSubtree; 

            updateAndRebalanceAlongPath(parentToLargestNodeInLeftSubtree->getUsername());
            
        }

    // No left subtree
    }else if(rightNode){

            // Shift right child into node 
            *(node->getDTree()) = *(rightNode->getDTree());

            // Nullify
            node->_right = nullptr;

            // Delete right child
            delete rightNode;

            // Traverse and update
            updateAndRebalanceAlongPath(node->getUsername());
        }

}

UNode* UTree::findLargestNode(UNode* node, UNode*& parent){
    if(node->_right == nullptr) return node;
    parent = node;
    return findLargestNode(node->_right, parent);
}


DNode* UTree::recursiveRemoveUser(UNode* node, string username){
    return nullptr;
}



/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
    return recursiveRetrieve(_root, username);

}

UNode* UTree::recursiveRetrieve(UNode* node, string username){
    if(node == nullptr){
        return nullptr;
    }


    if(username < node->getUsername()){
        return recursiveRetrieve(node->_left, username);
    }
    if(username > node->getUsername()){
        return recursiveRetrieve(node->_right, username);
    }

    return node;

}

/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
    
    UNode* userNode = retrieve(username);
    if(!userNode){
        return nullptr;
    }

    return userNode->getDTree()->retrieve(disc);
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
    UNode* userNode = retrieve(username);
    if(!userNode) return 0;

    return userNode->getDTree()->getNumUsers();
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
    recursiveClear(_root);
    _root = nullptr;
}

void UTree::recursiveClear(UNode* node){
    if(node == nullptr) return;
    recursiveClear(node->_left);
    recursiveClear(node->_right);
    delete node;
}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {
    recursivePrintUsers(_root);
}

void UTree::recursivePrintUsers(UNode* node) const {
    if(node == nullptr) return;
    recursivePrintUsers(node->_left);
    node->getDTree()->printAccounts();
    recursivePrintUsers(node->_right);
    cout << endl;

}


/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}


void UTree::dumpToString(std::stringstream& buffer) const {
    dumpToString(_root, buffer);
}

void UTree::dumpToString(UNode* node, std::stringstream& buffer) const {
    if(node == nullptr) return;

    buffer << "(";
    dumpToString(node->_left, buffer);
    buffer << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dumpToString(node->_right, buffer);
    buffer << ")";
}


/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {

    // If node is a leaf, its height is 0
    if(node->_left == nullptr && node->_right == nullptr){
        node->_height = 0;
    }
    
    else if(node->_left == nullptr && node->_right != nullptr){
        node->_height = 1 + node->_right->_height;
    }
    
    else if(node->_left != nullptr && node->_right == nullptr){
        node->_height = 1 + node->_left->_height;
    }
    
    else if(node->_left != nullptr && node->_right != nullptr){
        node->_height = 1 + std::max(node->_left->_height, node->_right->_height); 
    }


}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {


    if(node->_left == nullptr && node->_right == nullptr){
        return 0;
    }
    
    if(node->_left != nullptr && node->_right == nullptr){
        return node->_left->_height >= 1;
    }

    if(node->_left == nullptr && node->_right != nullptr){
        return node->_right->_height >= 1;
    }


    if(node->_left != nullptr && node->_right != nullptr){
        return (node->_left->_height > node->_right->_height + 1 || node->_right->_height > node->_left->_height + 1);
    }

    return 0;
}

//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
void UTree::rebalance(UNode*& node) {
    // Rebalance happens when abs(node_left_size - node_left_size) > 2
    // 4 cases

    UNode* leftNode = node->_left;
    UNode* rightNode = node->_right;

    int leftNodeHeight = (leftNode == nullptr ? -1 : leftNode->_height);
    int rightNodeHeight = (rightNode == nullptr ? -1 : rightNode->_height);

    // Left subtree
    UNode* leftOfLeftNode = nullptr;
    UNode* rightOfLeftNode = nullptr;

    // Right subtree
    UNode* rightOfRightNode = nullptr;
    UNode* leftOfRightNode = nullptr;

    if(leftNode != nullptr){
        leftOfLeftNode = leftNode->_left;
        rightOfLeftNode = leftNode->_right;
    }

    if(rightNode != nullptr){
        rightOfRightNode = rightNode->_right;
        leftOfRightNode = rightNode->_left;
    }

    int leftOfLeftNodeHeight = (leftOfLeftNode == nullptr ? -1 : leftOfLeftNode->_height);
    int rightOfLeftNodeHeight = (rightOfLeftNode == nullptr ? -1 : rightOfLeftNode->_height);

    int rightOfRightNodeHeight = (rightOfRightNode == nullptr ? -1 : rightOfRightNode->_height);
    int leftOfRightNodeHeight = (leftOfRightNode == nullptr ? -1 : leftOfRightNode->_height);



    // Tree is right heavy
    if(rightNodeHeight > leftNodeHeight + 1){

        // Right subtree is left heavy
        if(leftOfRightNodeHeight > rightOfRightNodeHeight){
            // Double left rotation

            rotateRight(rightNode);
            rotateLeft(node);
            return;
        }else{
        // Right subtree is right heavy
            // Single left rotation

            rotateLeft(node);
            return;
        }


    }

    // Tree is left heavy
    if(leftNodeHeight > rightNodeHeight + 1){

        // Left subtree is right heavy
        if(rightOfLeftNodeHeight > leftOfLeftNodeHeight){
            // Double right rotation

            rotateLeft(leftNode);
            rotateRight(node);
            return;
        }else{
        // Left subtree is left heavy
            // Single right rotation

            rotateRight(node);
            return;
        }
    }

}


void UTree::rotateLeft(UNode*& rootNode){
    /*
        root
        /  \
        A   pivot
            / \
            B  C


        to
     
            pivot
            /   \
         root    C   
         / \   
        a   b   

    */
    UNode* pivot = rootNode->_right;

    UNode* A = rootNode->_left;
    UNode* B = pivot->_left;
    UNode* C = pivot->_right;


    // Swap pivot with root
    DTree swapTree = DTree();
    swapTree = *(rootNode->getDTree());
    *(rootNode->getDTree()) = *(pivot->getDTree());
    *(pivot->getDTree()) = swapTree;

    // Update subtree connections
    rootNode->_left = pivot;

    rootNode->_right = C;
    pivot->_left = A;
    pivot->_right = B;

    // Update heights
    updateAlongPath(pivot->getUsername());

}

void UTree::rotateRight(UNode*& rootNode){
    /*
                root
                /  \
             pivot  A
              / \  
             C  B


                   
                to

            pivot
            /   \
          C    root   
                /  \
                B   A

    */

    UNode* pivot = rootNode->_left;

    UNode* A = rootNode->_right;
    UNode* B = pivot->_right;
    UNode* C = pivot->_left;


    // Swap pivot with root
    DTree swapTree = DTree();
    swapTree = *(rootNode->getDTree());
    *(rootNode->getDTree()) = *(pivot->getDTree());
    *(pivot->getDTree()) = swapTree;

    // Update subtree connections
    rootNode->_right = pivot;
    rootNode->_left = C;
    pivot->_right = A;
    pivot->_left = B;

    updateAlongPath(pivot->getUsername());

}


/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
//UNode* UTree::rebalance(UNode* node) {

//}
//----------------

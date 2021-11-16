/**
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"
#include "dtree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {

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


    if(recursiveInsert(_root, newAcct)){
        updateAndRebalanceAlongPath(newAcct);
        return true;
    }

    return false;

}


bool UTree::recursiveInsert(UNode* node, Account newAcct){
    if(newAcct.getUsername() < node->getUsername()){
        if(node->_left != nullptr){
            return recursiveInsert(node->_left, newAcct);
        }else{
            // Empty, insert
            UNode* newUNode = new UNode();
            node->_left = newUNode;
            // Add new account
            if(newUNode->getDTree()->insert(newAcct)){
                return true;
            }else{
                return false;
            }
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
            if(newUNode->getDTree()->insert(newAcct)){
                return true;
            }else{
                return false;
            }
        }
    }
    
    // Found match
    // Add new account to DTree
    if(node->getDTree()->insert(newAcct)){
        return true;
    }else{
        return false;
    }





}

void UTree::updateAndRebalanceAlongPath(Account acct){

    recursiveUpdateAndRebalanceAlongPath(_root, acct);

}

void UTree::recursiveUpdateAndRebalanceAlongPath(UNode* node, Account acct){



}





/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {
    return false;
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
    return nullptr;
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
    return 0;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
    recursiveClear(_root);
}

void UTree::recursiveClear(UNode* node){
    // Inorder traversal
    recursiveClear(node->_left);
    delete node;
    recursiveClear(node->_right);
}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {

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

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
    
    int nodeHeight = 0;
    if(node->_left != nullptr){
        nodeHeight += 1;
    }
    if(node->_right != nullptr){
        nodeHeight += 1;
    }

    node->_height = nodeHeight;


}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {
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
    // GP -> left -> left
    // GP -> right -> right
    // GP -> left -> right
    // GP -> right -> left
// -- OR --
}

/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
//UNode* UTree::rebalance(UNode* node) {

//}
//----------------

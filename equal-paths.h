//-----------------------------------------
// You may NOT change anything in this file
//-----------------------------------------
#ifndef EQUAL_PATHS_H
#define EQUAL_PATHS_H
#include <stdlib.h>

struct Node {
    int key;
    Node *left, *right;
    // Constructor for convenience
    Node(int k, Node* lt = nullptr, Node* rt = nullptr) :
        key(k), left(lt), right(rt)
    {}
};

/**
 * @brief Returns true if all paths from leaves to root are the same length (height),
 *        and false otherwise
 *
 *        Note: this doesn't mean we are checking if the tree is full, but just that
 *        any leaf node (wherever it may exist) has the same length path to the root 
 *        as all others.
 * 
 * @param root Pointer to the root of the tree to check for equal paths
 */
bool equalPaths(Node * root);

#endif
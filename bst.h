#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

    // DELETE THESE LATER - ONLY FOR TESTING
    Node<Key, Value>* nonVGetParent() const;
    Node<Key, Value>* nonVGetLeft() const;
    Node<Key, Value>* nonVGetRight() const;

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

// START OF TO DELETE LATER
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::nonVGetRight() const
{
    return right_;
}

template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::nonVGetLeft() const
{
    return left_;
}

template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::nonVGetParent() const
{
    return parent_;
}



// END OF TO DELETE LATER

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    int calculateHeightIfBalanced(const Node<Key, Value>* root) const;
    bool isBalancedHelper(const Node<Key, Value>* root) const;
    void destroyTree(Node<Key, Value>* root);
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    static bool isRightChild(Node<Key, Value>* current);
    static bool isLeftChild(Node<Key, Value>* current);
    Node<Key, Value>* thoroughInternalFind(Node<Key, Value>* curr, const Key& k) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO

    if (this->current_ == rhs.current_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return !(*this == rhs);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // make the iterator point to the successor

    this->current_ = successor(this->current_);

    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    /*
    Node<Key, Value>* insertNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    insertNode->setLeft(nullptr);
    insertNode->setRight(nullptr);
    bool inserted = false;

    std::cout << "Preparing to insert: " << insertNode->getKey() << std::endl;
    // case 1: tree is empty
    if (!root_)
    {
        root_ = insertNode;
        inserted = true;
        std::cout << "Made " << insertNode->getKey() << " the root" << std::endl;
    }
    else
    {
        // case 2: find a spot to insert
        Node<Key, Value>* curr = root_;
        std::cout << "trying root getters: " << std::endl;
        std::cout << "root->right(): ";
        std::cout << root_->getRight() << std::endl;
        std::cout << "root->left(): ";
        std::cout << root_->getLeft() << std::endl;

        std::cout << "curr: " << curr << std::endl;
        std::cout << "curr->right(): " << curr->getRight() << std::endl;

        while (!inserted)
        {
            if (curr->getKey() == insertNode->getKey())
            {
                // potential memory leak here
                curr->setValue(insertNode->getValue());
                inserted = true;
                delete insertNode;
                std::cout << "Updated value of " << curr->getKey() << std::endl;
                insertNode = nullptr;
            }
            else if (insertNode->getKey() < curr->getKey())
            {
                std::cout << "trying the left: " << std::endl;
                if (curr->getLeft()) 
                {
                    std::cout << "moving to the left of " << curr->getKey() << std::endl;
                    curr = curr->getLeft();
                }
                else
                {
                    curr->setLeft(insertNode);
                    insertNode->setParent(curr);
                    inserted = true;
                    std::cout << "Inserted " << insertNode->getKey() << " to the left of " << curr->getKey() << std::endl;
                    insertNode = nullptr;
                }
            }
            else
            {
                std::cout << "trying the right: " << std::endl;
                if (curr->getRight())
                {
                    std::cout << "moving to the right of " << curr->getKey() << std::endl;
                    curr = curr->getRight();
                }
                else
                {
                    curr->setRight(insertNode);
                    insertNode->setParent(curr);
                    inserted = true;
                    std::cout << "Inserted " << insertNode->getKey() << " to the right of " << curr->getKey() << std::endl;
                    insertNode = nullptr;
                }
            }
        }
    } 
    */
    
    // in another way
    Key insertKey = keyValuePair.first;
    Value insertValue = keyValuePair.second;

    // std::cout << "Preparing to insert: " << insertKey << std::endl;
    // empty tree - make the pair the root
    if (!root_)
    {
        root_ = new Node<Key, Value>(insertKey, insertValue, nullptr);
    }
    else
    {
        Node<Key, Value>* current = root_;
        bool beenInserted = false;

        while (!beenInserted)
        {
            if (insertKey == current->getKey())
            {
                current->setValue(insertValue);
                beenInserted = true;
            }
            else if (insertKey < current->getKey())
            {
                if (current->nonVGetLeft())
                {
                    current = current->nonVGetLeft();
                }
                else
                {
                    current->setLeft(new Node<Key, Value>(insertKey, insertValue, current));
                    beenInserted = true;
                }
            } 
            else
            {
                if (current->nonVGetRight())
                {
                    current = current->nonVGetRight();
                }
                else
                {
                    current->setRight(new Node<Key, Value>(insertKey, insertValue, current));
                    beenInserted = true;
                }
            }
        }
    }

    // print();
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* toRemove = internalFind(key);

    bool isRoot = false;

    if (!toRemove)
    {
        // node is not in tree
        return;
    }
    
    if (toRemove == root_)
    {
        isRoot = true;
    }

    if (!toRemove->getLeft() && !toRemove->getRight())
    {
        delete toRemove;
        root_ = nullptr;
    }
    else if (toRemove->getLeft() && !toRemove->getRight())
    {
        Node<Key, Value>* child = toRemove->getLeft();
        nodeSwap(child, toRemove);
        child->setLeft(toRemove->getLeft());
        child->setRight(toRemove->getRight());
        toRemove->getLeft()->setParent(child);

        if (isRoot)
        {
            root_ = child;
        }
        delete toRemove;
    }
    else if (!toRemove->getLeft() && toRemove->getRight())
    {
        Node<Key, Value>* child = toRemove->getRight();
        nodeSwap(child, toRemove);
        child->setLeft(toRemove->getLeft());
        child->setRight(toRemove->getRight());
        toRemove->getRight()->setParent(child);

        if (isRoot)
        {
            root_ = child;
        }

        delete toRemove;
    }
    else
    {
        // 2 child case - swap with predecessor and delete it
        Node<Key, Value>* pred = predecessor(toRemove);
        nodeSwap(pred, toRemove);
        

        /* fix up the removal
            - we now either have 1 or 0 children attached to toRemove
            - so let's use our code from above
        */

        if (!toRemove->getLeft() && !toRemove->getRight())
        {
            // toRemove now has 0 children
            delete toRemove;
        }
        else if (toRemove->getLeft() && !toRemove->getRight())
        {
            // to remove has a left child -- remove it
            Node<Key, Value>* child = toRemove->getLeft();
            nodeSwap(child, toRemove);
            child->setLeft(toRemove->getLeft());
            child->setRight(toRemove->getRight());
            toRemove->getLeft()->setParent(child);

            delete toRemove;
        }
        else 
        {
            // toRemove has a right child
            Node<Key, Value>* child = toRemove->getRight();
            nodeSwap(child, toRemove);
            child->setLeft(toRemove->getLeft());
            child->setRight(toRemove->getRight());
            toRemove->getRight()->setParent(child);

            delete toRemove;
        }
    }
    
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    Node<Key, Value>* pred = nullptr;

    if (!current)
    {
        return nullptr;
    }

    // case 1: has a left child - predecessor is right-most child of 
    // left subtree
    if (current->nonVGetLeft())
    {
        pred = current->nonVGetLeft();
        while (pred->nonVGetRight())
        {
            pred = pred->nonVGetRight();
        }
    } 
     // case 2: walk up the ancestor chain until we find the first 
     // right-child pointer
    else
    {
        bool found = false;
        while (current->nonVGetParent() && !found)
        {
            if (isRightChild(current))
            {
                pred = current->nonVGetParent();
                found = true;
            }
            current = current->nonVGetParent();
        }

    }

    return pred;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    if (!current)
    {
        return nullptr;
    }

    Node<Key, Value>* succ = nullptr;

    if (current->nonVGetRight())
    {
        succ = current->nonVGetRight();
        while (succ->nonVGetLeft())
        {
            succ = succ->nonVGetLeft();
        }
    }
    else
    {
        //bool foundSucc = false;
        while (current->nonVGetParent())
        {
            if (isLeftChild(current))
            {
                succ = current->nonVGetParent();
                //foundSucc = true;
                return succ;
            }
            else
            {
                current = current->nonVGetParent();
            }
            
        }
    }

    return succ;
}

template<class Key, class Value>
bool BinarySearchTree<Key, Value>::isRightChild(Node<Key, Value>* current)
{
    bool isRight = false;

    if (!current)
    {

    }
    else if (!current->nonVGetParent()) {
        // current is a root node so it can't be a right child
    } 
    else if (current->nonVGetParent()->nonVGetRight() == current)
    {
        isRight = true;
    }

    return isRight;
}

template<class Key, class Value>
bool BinarySearchTree<Key, Value>::isLeftChild(Node<Key, Value>* current)
{
    bool isLeft = false;

    if (!current)
    {

    }
    else if (!current->nonVGetParent()) {
        // current is a root node so it can't be a left child
    } 
    else if (current->nonVGetParent()->nonVGetLeft() == current)
    {
        isLeft = true;
    }
    return isLeft;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    destroyTree(root_);

    root_ = nullptr;
    
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::destroyTree(Node<Key, Value>* root)
{
    if (!root)
    {
        return;
    }

    destroyTree(root->nonVGetLeft());
    destroyTree(root->nonVGetRight());
    delete root;
    root = nullptr;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* currentSmallest = root_;
    while (currentSmallest->nonVGetLeft()) 
    {
        currentSmallest = currentSmallest->nonVGetLeft();
    }

    return currentSmallest;
    
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* finder = root_;
    bool found = false;
    while (!found)
    {
        if (!finder)
        {
            // not in tree, return nullptr
            found = true;
        }
        else if (finder->getKey() == key)
        {
            found = true;
        }
        else if (key < finder->getKey()) 
        {
            finder = finder->nonVGetLeft();
        } 
        else 
        {
            finder = finder->nonVGetRight();
        }
    }

    return finder;
    
}

// Searches the entire tree structure, even if it is not a proper BST.
// Used only for when we remove nodes and need to still retrieve a node
// even if the tree isn't a BST.
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::thoroughInternalFind(Node<Key, Value>* curr, const Key& k) const
{
    if (!curr)
    {
        return nullptr;
    }
    else if (curr->getKey() == k)
    {
        return curr;
    }

    Node<Key, Value>* left = curr->getLeft();
    Node<Key, Value>* right = curr->getRight();

    return thoroughInternalFind(left, k);
    return thoroughInternalFind(right, k);

    
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return isBalancedHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(const Node<Key, Value>* root) const
{
    if (!root) 
    {
		return true;
	}
	if ((std::abs(calculateHeightIfBalanced(root->getLeft()) - calculateHeightIfBalanced(root->getRight())) <= 1) &&
	(isBalancedHelper(root->getLeft())) && (isBalancedHelper(root->getRight()))) 
    {
		return true;
	} else 
    {
		return false;
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(const Node<Key, Value>* root) const
{
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) {
        return 0;
    }

	return std::max(1 + calculateHeightIfBalanced(root->getLeft()), 1 + calculateHeightIfBalanced(root->getRight()));
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif

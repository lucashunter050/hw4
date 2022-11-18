#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* node);
    void rotateRight(AVLNode<Key, Value>* node);
    bool zigZig(const AVLNode<Key, Value>* node) const;
    bool zigZag(const AVLNode<Key, Value>* node) const;
    void insertFix(AVLNode<Key, Value>* node1, AVLNode<Key, Value>* node2);
    void removeFix(AVLNode<Key, Value>* node, int8_t diff);
    AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* node);

    static bool isRightAVLChild(AVLNode<Key, Value>* current);
    static bool isLeftAVLChild(AVLNode<Key, Value>* current);
    bool outOfBalance(const AVLNode<Key, Value>* current) const;

    void removeZeroAVLChildren(AVLNode<Key, Value>* current);
    void removeWithLeftAVLChild(AVLNode<Key, Value>* current);
    void removeWithRightAVLChild(AVLNode<Key, Value>* current);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    Key insertKey = new_item.first;
    Value insertValue = new_item.second;
    if (this->root_ == nullptr)
    {
        this->root_ = new AVLNode<Key, Value>(insertKey, insertValue, nullptr);
    }
    else
    {
        AVLNode<Key, Value>* current = this->root_;
        bool beenInserted = false;

        while (!beenInserted)
        {
            if (insertKey == current->getKey())
            {
                // just reset the value
                current->setValue(insertValue);
                beenInserted = true;
            }
            else if (insertKey < current->getKey())
            {
                if (current->getLeft())
                {
                    current = current->getLeft();
                }
                else
                {
                    // make the new node a left child and update balance
                    current->setLeft(new AVLNode<Key, Value>(insertKey, insertValue, current));
                    beenInserted = true;
                    current->setBalance(current->getBalance() - 1);
                    current = current->getLeft();
                    if (current->getParent()->getParent())
                    {
                        //current->getParent()->setBalance(current->getParent()->getBalance() - 1);
                        if (current->getParent()->getBalance() != 0)
                        {
                            this->insertFix(current->getParent(), current);
                        }
                    }
                }
            } 
            else
            {
                if (current->getRight())
                {
                    current = current->getRight();
                }
                else
                {
                    // make the new node a right child and update balance
                    current->setRight(new AVLNode<Key, Value>(insertKey, insertValue, current));
                    beenInserted = true;
                    current->setBalance(current->getBalance() + 1);
                    if (current->getParent())
                    {
                        current->getParent()->setBalance(current->getParent()->getBalance() + 1);
                    }
                    current = current->getRight();

                    if (current->getParent()->getParent())
                    {
                        //current->getParent()->setBalance(current->getParent()->getBalance() - 1);
                        if (current->getParent()->getBalance() != 0)
                        {
                            this->insertFix(current->getParent(), current);
                        }
                    }
                }
            }
        }

        if (outOfBalance(current->getParent()->getParent()))
        {
            
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* node1, AVLNode<Key, Value>* node2)
{
    if (!node1 || !node1->getParent())
    {
        return;
    }
    
    if (isLeftAVLChild(node1))
    {
        node1->getParent()->setBalance(node1->getParent()->getBalance() - 1);
        if (node1->getParent()->getBalance() == 0)
        {
            return;
        }
        else if (node1->getParent()->getBalance() == -1)
        {
            insertFix(node1->getParent(), node1);
        }
        else
        {
            // balance of node1->parent == -2
            if (zigZig(node2))
            {
                rotateRight(node1->getParent());
                node1->setBalance(0);
                node2->setBalance(0);
            }
            else
            {
                rotateLeft(node1);
                rotateRight(node1->getParent());
                if (node2->getBalance() == -1)
                {
                    node1->setBalance(0);
                    node1->getParent()->setBalance(1);
                    node2->setBalance(0);
                }
                else if (node2->getBalance() == 0)
                {
                    node1->setBalance(0);
                    node1->getParent()->setBalance(0);
                    node2->setBalance(0);
                }
                else
                {
                    node1->setBalance(-1);
                    node1->getParent()->setBalance(0);
                    node2->setBalance(0);
                }
            }
        }
    }
    else
    {
        node1->getParent()->setBalance(node1->getParent()->getBalance() + 1);
        if (node1->getParent()->getBalance() == 0)
        {
            return;
        }
        else if (node1->getParent()->getBalance() == 1)
        {
            insertFix(node1->getParent(), node1);
        }
        else
        {
            // balance of node1->parent == 2
            if (zigZig(node2))
            {
                rotateLeft(node1->getParent());
                node1->setBalance(0);
                node2->setBalance(0);
            }
            else
            {
                rotateRight(node1);
                rotateLeft(node1->getParent());
                if (node2->getBalance() == 1)
                {
                    node1->setBalance(0);
                    node1->getParent()->setBalance(-1);
                    node2->setBalance(0);
                }
                else if (node2->getBalance() == 0)
                {
                    node1->setBalance(0);
                    node1->getParent()->setBalance(0);
                    node2->setBalance(0);
                }
                else
                {
                    node1->setBalance(1);
                    node1->getParent()->setBalance(0);
                    node2->setBalance(0);
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* toRemove = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    std::cerr << "removing " << key << std::endl;

    if (!this->root_)
    {
        // tree is empty - return by default
        return;
    }

    if (!toRemove)
    {
        // node is not in tree
        return;
    }

    // removal cases - rewrite these functions 

    if (!toRemove->getLeft() && !toRemove->getRight())
    {
        this->removeZeroAVLChildren(toRemove);
    }
    else if (toRemove->getLeft() && !toRemove->getRight())
    {
        this->removeWithLeftAVLChild(toRemove);
    }
    else if (!toRemove->getLeft() && toRemove->getRight())
    {
        this->removeWithRightAVLChild(toRemove);
    }
    else
    {
        // 2 child case
        bool isRoot = false;
        if (toRemove == this->root_)
        {
            isRoot = true;
        }
        AVLNode<Key, Value>* pred = predecessor(toRemove);
        nodeSwap(pred, toRemove);
        if (isRoot)
        {
            this->root_ = pred;
        }

        int8_t diff = 0;
        AVLNode<Key, Value>* parent = toRemove->getParent();

        if (parent)
        {
            if (isLeftAVLChild(toRemove))
            {
                diff = 1;
            }
            else
            {
                diff = -1;
            }
        }

        // delete toRemove - call the right functions


        removeFix(parent, diff);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int8_t diff)
{
    if (!node)
    {
        return;
    }

    uint8_t ndiff = 0;
    if (isLeftAVLChild(node))
    {
        ndiff = 1;
    }
    else
    {
        ndiff = -1;
    }

    AVLNode<Key, Value>* parent = node->getParent();
    if (node->getBalance() + diff == -2)
    {
        AVLNode<Key, Value>* left = node->getLeft();
        
        if (left->getBalance() == -1)
        {
            rotateRight(node);
            node->setBalance(0);
            left->setBalance(0);

            removeFix(parent, ndiff);
        }
        else if (left->getBalance() == 0)
        {
            rotateRight(node);
            node->setBalance(-1);
            left->setBalance(1);
        }
        else
        {
            // left->getBalance == +1

            AVLNode<Key, Value>* g = left->getRight();
            rotateLeft(left);
            rotateRight(node);

            if (g->getBalance() == 1)
            {
                g->setBalance(0);
                node->setBalance(0);
                left->setBalance(-1);
            }
            else if (g->getBalance() == 0)
            {
                g->setBalance(0);
                node->setBalance(0);
                left->setBalance(0);
            }
            else
            {
                g->setBalance(0);
                node->setBalance(1);
                left->setBalance(0);
            }

            removeFix(parent, ndiff);
        }
    }
    else if (node->getBalance() + diff == -1)
    {
        node->setBalance(-1);
    }
    else if (node->getBalance() + diff == 0)
    {
        node->setBalance(0);
        removeFix(parent, ndiff);
    }
    else if (node->getBalance() + diff == 2)
    {
        // copy case above but flip right/left and +/-
        AVLNode<Key, Value>* right = node->getRight();
        
        if (right->getBalance() == 1)
        {
            rotateLeft(node);
            node->setBalance(0);
            left->setBalance(0);

            removeFix(parent, ndiff);
        }
        else if (right->getBalance() == 0)
        {
            rotateLeft(node);
            node->setBalance(1);
            left->setBalance(-1);
        }
        else
        {
            // left->getBalance == +1

            AVLNode<Key, Value>* g = right->getLeft();
            rotateLeft(right);
            rotateRight(node);

            if (g->getBalance() == 1)
            {
                g->setBalance(0);
                node->setBalance(0);
                right->setBalance(-1);
            }
            else if (g->getBalance() == 0)
            {
                g->setBalance(0);
                node->setBalance(0);
                left->setBalance(0);
            }
            else
            {
                g->setBalance(0);
                node->setBalance(-1);
                right->setBalance(0);
            }

            removeFix(parent, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeZeroAVLChildren(AVLNode<Key, Value>* removeMe)
{
    if (!removeMe->getParent())
    {
        // we are removing the last node in the tree so root_ is set to nullptr
        this->root_ = nullptr;
    }
    else if (isLeftChild(removeMe))
    {
        removeMe->getParent()->setLeft(nullptr);
    } 
    else
    {
        removeMe->getParent()->setRight(nullptr);
    }

    delete removeMe;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeWithLeftAVLChild(AVLNode<Key, Value>* removeMe)
{
    bool isRoot = false;
    if (removeMe == this->root_)
    {
        isRoot = true;
    }
    AVLNode<Key, Value>* child = removeMe->getLeft();
    nodeSwap(child, removeMe);
    child->setLeft(removeMe->getLeft());
    child->setRight(removeMe->getRight());
    if (removeMe->getLeft())
    {
        removeMe->getLeft()->setParent(child);
    }
    // add another if statement in case removeme has a right child after the swap
    if (removeMe->getRight())
    {
        removeMe->getRight()->setParent(child);
    }

    delete removeMe;

    if (isRoot)
    {
        this->root_ = child;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeWithRightAVLChild(AVLNode<Key, Value>* removeMe)
{
    bool isRoot = false;
    if (removeMe == this->root_)
    {
        isRoot = true;
    }
    AVLNode<Key, Value>* child = removeMe->getRight();
    nodeSwap(child, removeMe);
    child->setLeft(removeMe->getLeft());
    child->setRight(removeMe->getRight());
    if (removeMe->getRight())
    {
        removeMe->getRight()->setParent(child);
    }
    if (removeMe->getLeft())
    {
        removeMe->getLeft()->setParent(child);
    }
    
    delete removeMe;

    if (isRoot)
    {
        this->root_ = child;
    }
}


template<class Key, class Value>
bool AVLTree<Key, Value>::zigZig(const AVLNode<Key, Value>* node) const
{
    // sees if the current node created a zig-zig condition
    if (!node)
    {
        return false;
    }

    if (!node->getParent())
    {
        return false;
    }

    if (!node->getParent()->getParent())
    {
        return false;
    }

    if (isRightAVLChild(node) && isRightAVLChild(node->getParent()) || 
        isLeftAVLChild(node) && isLeftAVLChild(node->getParent()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    

template<class Key, class Value>
bool AVLTree<Key, Value>::zigZag(const AVLNode<Key, Value>* node) const
{
    // sees if the current node creates a zig-zag condition
    if (!node)
    {
        return false;
    }

    if (!node->getParent())
    {
        return false;
    }

    if (!node->getParent()->getParent())
    {
        return false;
    }

    if (isRightAVLChild(node) && isLeftAVLChild(node->getParent()) || 
        isLeftAVLChild(node) && isRightAVLChild(node->getParent()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightAVLChild(AVLNode<Key, Value>* current)
{
    if (!current)
    {
        return false
    }
    else if (!current->getParent()) {
        // current is a root node so it can't be a right child
        return false;
    } 
    else if (current->getParent()->getRight() == current)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftAVLChild(AVLNode<Key, Value>* current)
{
    if (!current)
    {
        return false
    }
    else if (!current->getParent()) {
        // current is a root node so it can't be a left child
        return false;
    } 
    else if (current->getParent()->getLeft() == current)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::outOfBalance(const AVLNode<Key, Value>* current) const
{
    if (current->getBalance() < -1 || current->getBalance() > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Key, class Value>
void rotateLeft(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* child = node->getRight();
    child->setParent(node->getParent());
    node->setRight(child->getLeft());
    child->setLeft(node);
    node->setParent(child);
}

template<class Key, class Value>
void rotateRight(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* child = node->getLeft();
    child->setParent(node->getParent());
    node->setLeft(child->getRight());
    child->setRight(node);
    node->setParent(child);

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif

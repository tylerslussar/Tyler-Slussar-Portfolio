//
// Tyler Slussar CS 361 9:30AM
// 
//  AVLTree.hpp
//  AVLTreeParentTemplate
//
//  Created by David M Reed on 5/18/21.
// 
//

#ifndef AVLTree_h
#define AVLTree_h

#include "BinaryTreeNode.hpp"

template <typename T>
class AVLTree {

public:

    /**
     constructor
     */
    AVLTree();


    /** copy constructor
     @param source AVLTree to copy
     */
    AVLTree(const AVLTree<T>& source);

    /** assignment operator

     @param source object to copy
     @returns *this which is now a copy of src
     */
    AVLTree<T>& operator=(const AVLTree<T>& source);

    /** insert item into tree
     @param item value to insert
     @pre item is not already in the tree
     @post item is inserted into tree and tree is balanced according to AVL rules
     */
    void insert(const T& item);

    /**
     search for item in tree

     @param item item value to search for
     @return BinaryTree containing item or nullptr if item not found
     */
    std::shared_ptr<BinaryTreeNode<T>> find(const T& item) const;


    /**
     returns the node containing the minimum value in the tree

     @return the node containing the minimum value in the tree
     */
    std::shared_ptr<BinaryTreeNode<T>> minimumNode() const;

    /**
     returns the node containing the maximum value in the tree

     @return the node containing the maximum value in the tree
     */
    std::shared_ptr<BinaryTreeNode<T>> maximumNode() const;

    /**
     returns the BinaryTreeNode containing the element in the tree that is the next smallest element compared to the element at the node passed as the parameter

     @param node BinaryTreeNode whose element we want to find the next smallest element
     @return the BinaryTreeNode containing the element in the tree that is the next smallest element compared to the element at the node passed as the parameter
     */
    std::shared_ptr<BinaryTreeNode<T>> nextSmallestNode(std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     returns the BinaryTreeNode containing the element in the tree that is the next largest element compared to the element at the node passed as the parameter

     @param node BinaryTreeNode whose element we want to find the next largest element
     @return the BinaryTreeNode containing the element in the tree that is the next largest element compared to the element at the node passed as the parameter
     */
    std::shared_ptr<BinaryTreeNode<T>> nextLargestNode(std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     print items (one item per line) tree using inorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in inorder order
     */
    void printInorder() const;

    /**
     print items (one item per line) tree using preorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in preorder order
     */
    void printPreorder() const;

    /**
     print items (one item per line) tree using postorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in postorder order
     */
    void printPostorder() const;

    /**
     returns number of items in tree

     @returns number of items in tree
     */
    int size() const { return _size; }

private:
    /**
     recursively makes a copy of the subtree rooted at node

     @param rootNode root of the subtree to copy
     @post a copy (new nodes) of the entire subtree rooted at node is created
     @returns the root BinaryTreeNode of a copy of the subtree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> _copyNodes(const std::shared_ptr<BinaryTreeNode<T>>& rootNode) const;

    /**
     search for item in subtree rooted at node

     @param node BinaryTreeNode root of subtree to search in
     @param item value to search for
     @returns BinaryTreeNode containing item or nullptr if not item not found
     */
    std::shared_ptr<BinaryTreeNode<T>> findHelp(const std::shared_ptr<BinaryTreeNode<T>> node, const T& item) const;

    /**
     helper method for minimumNode

     @param node the root of the tree to find the smallest element in this subtree
     @return the node containing the smallest element in the tree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> minimumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     helper method for maximumNode

     @param node the root of the tree to find the largest element in this subtree
     @return the node containing the largest element in the tree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> maximumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     deallocates entire tree

     @post entire tree is deallocated and _root is set to nullptr
     */
    void clear();

    /**
     insert item into subtree with root node

     @param node BinaryTreeNode root of tree to insert into
     @param item value to insert
     @pre item is not already in the tree
     @post item is inserted into tree and tree is balanced according to AVL rules
     */
    void insertHelp(std::shared_ptr<BinaryTreeNode<T>>& node, const T& item);

    /**
     print items (one item per line) in subtree rooted at node using inorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     print items (one item per line) in subtree rooted at node using preorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     print items (one item per line) in subtree rooted at node using postorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const;

    /**
     rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into left subtree of left child of node by performing a clockwise rotation

     @param node root of subtree that needs rebalanced and only one insertion has been performed since tree was balanced
     @pre node is deepest node whose left subtree has height two more than its right subtree and only one insertion has been performed since tree was balanced
     @post tree is rebalanced
     */
    void leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node);

    /**
     rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into right subtree of right child of node by performing a counter-clockwise rotation

     @param node root of subtree that needs rebalanced
     @pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
     @post tree is rebalanced
     */
    void rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node);

    /**
     rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into right subtree of left child of node by performing two rotations

     @param node root of subtree that needs rebalanced
     @pre node is deepest node whose left subtree has height two more than its right subtree
     @post tree is rebalanced
     */
void rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>>& node);

/**
 rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into left subtree of right child of node by performing two rotations

 @param node root of subtree that needs rebalanced
 @pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
 @post tree is rebalanced
 */
void leftRightRotate(std::shared_ptr<BinaryTreeNode<T>>& node);

// pointer to root node of tree
std::shared_ptr<BinaryTreeNode<T>> _root;
// number of items in the tree
int _size;
};

//--------------------------------------------------------------------

// maximum function for use with tree heights
inline int max(int a, int b) {
    return a > b ? a : b;
}

//--------------------------------------------------------------------
template <typename T>
AVLTree<T>::AVLTree() {
    
    // constructor
    _size = 0;
    _root = nullptr;
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& source) {
   
    // copy constructor
    // set the root to the copy
    _root = _copyNodes(source._root);
    _size = source._size;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& source) {

    // assignment operator
    if (this != &source) {
        _root = _copyNodes(source._root);
        _size = source._size;
    }
    return *this;
}

template <typename T>
void AVLTree<T>::insert(const T& item) {
    
    // uses the recursive helper method
    insertHelp(_root, item);
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::find(const T& item) const {

    // uses the recursive helper method
    return findHelp(_root, item);
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::minimumNode() const {

    // uses the recursive helper method
    return minimumNodeHelp(_root);
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::maximumNode() const {

    // uses the recursive helper method
    return maximumNodeHelp(_root);
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::nextSmallestNode(std::shared_ptr<BinaryTreeNode<T>> node) const {

    // assigns new nodes that are used for differnet things
    std::shared_ptr<BinaryTreeNode<T>> other, largestSmallerNode, checkNode;
    largestSmallerNode = nullptr;
    other = node;

    // travel through the tree by going left
    while (other->_left != nullptr){
        
        // check and see if the right size is still less than node
        if (other->_right->_item < node->_item) {
            other = other->_right;
            largestSmallerNode = other;
        }

        if ((other->_left != nullptr) and (other->_left->_item < node->_item)) {
            other = other->_left;
            largestSmallerNode = other;

           
            if (other->_right->_item < node->_item) {
                other = other->_right;
                largestSmallerNode = other;
            }
        }
    }
    // if found returns the node
    if (largestSmallerNode != nullptr) {
        return largestSmallerNode;
    }
    
    // travel through the tree by going up
    while (other->_parent.lock() != nullptr) {
        checkNode = other;
        other = other->_parent.lock();
      
        if (other->_item < node->_item) {
            largestSmallerNode = other;
        }
            if (other->_left != checkNode) {
                if ((other->_parent.lock() == nullptr) and (other->_item < node->_item)) {
                    return largestSmallerNode;
                }
                if ((other->_parent.lock()->_item > other->_item) or (other->_parent.lock()->_item < other->_item)){
                    return largestSmallerNode;
                }
                other = other->_parent.lock();
                if (other->_item < node->_item) {
                    largestSmallerNode = other;
                }
        }
    }
    // if no node is found
    return nullptr;                      
}


template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::nextLargestNode(std::shared_ptr<BinaryTreeNode<T>> node) const {
    
    // assigns new nodes that are used for differnet things
    std::shared_ptr<BinaryTreeNode<T>> other, smallestLargerNode, checkNode;
    smallestLargerNode = nullptr;
    other = node;

    // travel through the tree by going right
    while (other->_right != nullptr) {

        if (other->_left->_item > node->_item) {
            other = other->_left;
            smallestLargerNode = other;
        }

        if ((other->_right != nullptr) and (other->_right->_item > node->_item)) {
            other = other->_right;
            smallestLargerNode = other;


            if ((other->_left != nullptr) and (other->_left->_item > node->_item)) {
                other = other->_left;
                smallestLargerNode = other;
            }
        }
    }
    // if the node is found
    if (smallestLargerNode != nullptr) {
        return smallestLargerNode;
    }

    // travel through the tree by going up
    while (other->_parent.lock() != nullptr) {
        checkNode = other;
        other = other->_parent.lock();

        if (other->_item > node->_item) {
            smallestLargerNode = other;
        }
        if (other->_right != checkNode) {
            if ((other->_parent.lock() == nullptr) and (other->_item < node->_item)) {
                return smallestLargerNode;
            }
            if ((other->_parent.lock() == nullptr) or (other->_parent.lock()->_item > other->_item) or (other->_parent.lock()->_item < other->_item)){
                return smallestLargerNode;
            }
            other = other->_parent.lock();
            if (other->_item < node->_item) {
                smallestLargerNode = other;
            }
        }
    }
    // if no node is found
    return nullptr;
}


template <typename T>
void AVLTree<T>::printInorder() const {
    
    // uses the recursive helper method
    printInorderHelp(_root);
}

template <typename T>
void AVLTree<T>::printPostorder() const {

    // uses the recursive helper method
    printPostorderHelp(_root);
}

template <typename T>
void AVLTree<T>::printPreorder() const {
   
    // uses the recursive helper method
    printPreorderHelp(_root);
}


template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::_copyNodes(const std::shared_ptr<BinaryTreeNode<T>>& rootNode) const {
    
    
    std::shared_ptr<BinaryTreeNode<T>> newNode;

    if (rootNode != nullptr) {
        newNode = std::make_shared<BinaryTreeNode<T>>(rootNode->_item);
        // recursives copies left node and assign parents
        newNode->_left = _copyNodes(rootNode->_left);
        if (newNode->_left != nullptr) {
            newNode->_left->_parent = newNode;
        }
        // recursives copies right node and assign parents
        newNode->_right = _copyNodes(rootNode->_right);
        if (newNode->_right != nullptr) {
            newNode->_right->_parent = newNode;
        }
        newNode->_height = rootNode->_height;
    }
    else {
        return nullptr;
    }
   
    return newNode;

}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::findHelp(const std::shared_ptr<BinaryTreeNode<T>> node, const T& item) const {
    
    // recursively calls until node is found
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->_item == item) {
        return node;
    }


    if (node->_item < item) {
        return findHelp(node->_right, item);
    }
    else {
       return findHelp(node->_left, item);
    }
   
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::minimumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {
    
    // when at the bottom of tree return the node found
    if (node->_height == 0) {
        return node;
    }
    return minimumNodeHelp(node->_left);
}

template <typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::maximumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

    // when at the bottom of tree return the node found
    if (node->_height == 0) {
        return node;
    }
    return maximumNodeHelp(node->_right);
}

template <typename T>
void AVLTree<T>::clear() {

    // deallocate the root 
    _root = nullptr;
    _size = 0;
}

template <typename T>
void AVLTree<T>::insertHelp(std::shared_ptr<BinaryTreeNode<T>>& node, const T& item) {
    
    // recursively insert node
    if (node == nullptr) {
        node = std::make_shared<BinaryTreeNode<T>>(item);
        _size += 1;
    }

    else if (item < node->_item) {
        insertHelp(node->_left, item);
           
            // assigns parent
           node->_left->_parent = node;

        if (getHeight(node->_left) - getHeight(node->_right) == 2) {
           
            if (item < node->_left->_item) {
                leftSingleRotate(node);
            }
            else {
                 rightLeftRotate(node);
            }
        }
    }
    else {
        insertHelp(node->_right, item);
            
           // assigns parent
           node->_right->_parent = node;
        
        if (getHeight(node->_right) - getHeight(node->_left) == 2) {

            if (item > node->_right->_item) {
                 rightSingleRotate(node);
            }
            else {
                leftRightRotate(node);  
            }
        }
    }
    node->_height = max(getHeight(node->_left), getHeight(node->_right)) + 1;
}



template <typename T>
void AVLTree<T>::printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

    // recursively prints the order as LNR
    if (node == nullptr) {
        return;
    }
    printInorderHelp(node->_left);
    cout << node->_item << "\n";
    printInorderHelp(node->_right);
}

template <typename T>
void AVLTree<T>::printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {
   
    // recursively prints the order as NLR
    if (node == nullptr) {
        return;
    }
    cout << node->_item << "\n";
    printPreorderHelp(node->_left);
    printPreorderHelp(node->_right);
}

template <typename T>
void AVLTree<T>::printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {
    
    // recursively prints the order as LRN
    if (node == nullptr) {
        return;
    }
    printPostorderHelp(node->_left);
    printPostorderHelp(node->_right);
    cout << node->_item << "\n";
}


template <typename T>
void AVLTree<T>::leftSingleRotate(std::shared_ptr < BinaryTreeNode<T>>& node) {

    auto grandparent = node;
    auto nodeParent = node->_left;
    grandparent->_left = nodeParent->_right;
    nodeParent->_right = grandparent;
    
    // assigns parent
    if (node->_left != nullptr){
        node->_left->_parent = grandparent;
    }
   
    node = nodeParent;
    
    grandparent->_parent = nodeParent;
    nodeParent->_parent.reset();

    grandparent->_height = max(getHeight(grandparent->_left),
        getHeight(grandparent->_right)) + 1;

    nodeParent->_height = max(getHeight(nodeParent->_left),
        getHeight(nodeParent->_right)) + 1;
}

template <typename T>
void AVLTree<T>::rightSingleRotate(std::shared_ptr < BinaryTreeNode<T>>& node) {
   
    auto grandparent = node;
    auto nodeParent = node->_right;
    grandparent->_right = nodeParent->_left;
    nodeParent->_left = grandparent;
    nodeParent->_right->_parent = nodeParent;

    // assigns parent
    if (node->_right != nullptr) {
        node->_right->_parent = grandparent;
    }

    node = nodeParent;
    
    grandparent->_parent = nodeParent;
    nodeParent->_parent.reset();


    grandparent->_height = max(getHeight(grandparent->_right),
        getHeight(grandparent->_left)) + 1;

    nodeParent->_height = max(getHeight(nodeParent->_right),
        getHeight(nodeParent->_left)) + 1;
}

template <typename T>
void AVLTree<T>::rightLeftRotate(std::shared_ptr < BinaryTreeNode<T>>& node) {
    
     // double rotation
     rightSingleRotate(node->_left);
     leftSingleRotate(node);
    
}

template <typename T>
void AVLTree<T>::leftRightRotate(std::shared_ptr < BinaryTreeNode<T>>& node) {

    // double rotation
    leftSingleRotate(node->_right);
    rightSingleRotate(node);
}
//--------------------------------------------------------------------

#endif /* AVLTree_h */
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP
#include "binarytree.h"
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;


template <typename T>
int BinaryTree<T>::countLeafNodes() {
  // TODO: your code here
  return this->countLeafNodes(root);;
}

template <typename T>
int BinaryTree<T>::countLeafNodes(BinaryTree<T>::Node * subroot)
{

  if(subroot == NULL){
    return 0;
  }

  if (subroot->left == NULL && subroot->right == NULL)
  {
    return 1;
  }

  int count = this->countLeafNodes(subroot->left) + this->countLeafNodes(subroot->right);

  return count;

}


/*************************************
 * PROVIDED CODE BELOW - do not modify *
 *************************************/

/**
 * Constructor to create an empty tree.
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root(NULL) {
  /* nothing */
}

/**
 * Inserts into the BinaryTree, using BST insert algorithm.
 * @param elem The element to insert
 */
template <typename T>
void BinaryTree<T>::insert(const T& elem) {
  insert(root, elem);
}

template <typename T>
void BinaryTree<T>::insert(Node*& node, const T& elem)
{
    // If we're at a NULL pointer, we can put our element here
    if (node == NULL)
        node = new Node(elem);

    // Go left or right
    else if (elem < node->elem)
        insert(node->left, elem);
    else
        insert(node->right, elem);
}

#endif

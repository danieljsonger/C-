#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class BinaryTree {
  private:
    struct Node {
        T elem;
        Node* left;
        Node* right;
        Node(const T& element) : elem(element), left(NULL), right(NULL) { }
    };

    Node* root;
    int countLeafNodes(BinaryTree<T>::Node * subroot);
    void insert(Node*& node, const T& elem);

  public:
    BinaryTree();
    int countLeafNodes();
    void insert(const T& elem);
};

#include "binarytree.cpp"

#endif

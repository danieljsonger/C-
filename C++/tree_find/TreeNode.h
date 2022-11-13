#pragma once

#include <cstddef>

class TreeNode {
    private:
        int data_;
        TreeNode *left_;
        TreeNode *right_;

    public:
        TreeNode(int data=0, TreeNode *left=NULL, TreeNode *right=NULL);
        ~TreeNode();
        int findMax() const;

        int getData() const;
        TreeNode *getLeft() const;
        TreeNode *getRight() const;

        // Here is the signature of the code you will write

        const TreeNode *find(int value) const;
};

bool equal(TreeNode *n1, TreeNode *n2);

#include <iostream>
#include "TreeNode.h"

using namespace std;

int main() {

    TreeNode *two = new TreeNode(2);
  
    TreeNode *example =
        new TreeNode(8,
                new TreeNode(4,
                    two,
                    new TreeNode(5)),
                new TreeNode(14,
                    new TreeNode(12),
                    new TreeNode(19)));

    TreeNode *fourteen = example->getRight();

    cout << "Result of find(2): " << (two == example->find(2)) << endl;
    cout << "Result of find(14): " << (fourteen == example->find(14)) << endl;
    cout << "Result of find(11): " << (nullptr == example->find(11)) << endl;

    // Clean up
    delete example;
}

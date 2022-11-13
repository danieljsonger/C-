/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * center = t->right;
    t->right = center->left;
    center->left = t;
    t = center;
    center->left->height = (heightOrNeg1(center->left->right) > heightOrNeg1(center->left->left)) ? heightOrNeg1(center->left->right) + 1 : heightOrNeg1(center->left->left) + 1;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * center = t->left;
    t->left = center->right;
    center->right = t;
    t = center;
    center->right->height = (heightOrNeg1(center->right->right) > heightOrNeg1(center->right->left)) ? heightOrNeg1(center->right->right) + 1 : heightOrNeg1(center->right->left) + 1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) { return; }

    int bal = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (bal >= 2) {
        int my_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (my_balance >= 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    } else if (bal <= -2) {
        int my_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (my_balance <= -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }

    subtree->height = (heightOrNeg1(subtree->right) > heightOrNeg1(subtree->left)) ? heightOrNeg1(subtree->right) + 1 : heightOrNeg1(subtree->left) + 1;

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) { subtree = new Node(key,value); }

    if (subtree->key > key) { insert(subtree->left, key, value); }
    else if (subtree->key < key) { insert(subtree->right, key, value); }
    else { subtree->value = value; }
    
    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * current = subtree->left;
            while (current->right){
                current = current->right;
            }
            swap(subtree,current);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (!subtree->left && subtree->right) {
                Node * temp = subtree->right;
                delete subtree;
                subtree = temp;
            }
            
            if (subtree->left && !subtree->right) {
                Node * temp = subtree->left;
                delete subtree;
                subtree = temp;
            }
        }
        // your code here
    }
    rebalance(subtree);
}

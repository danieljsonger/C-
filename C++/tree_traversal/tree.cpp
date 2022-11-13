#ifndef TREE_CPP
#define TREE_CPP

#include "tree.h"

template <class T>
Tree<T>::Iterator::Iterator(Tree::Node *root) : curr_(root) {
	// TODO: your code here
	stack.push(root);
	if(curr_ != NULL){ 
		while (!stack.empty() && curr_->data_ <= 0)
		{
			++(*this);
		}
	}
}

template <class T>
typename Tree<T>::Iterator & Tree<T>::Iterator::operator++() {

	// TODO: your code here
	if (!stack.empty()){
		curr_ = stack.top();
		stack.pop();
		if (curr_->left_ != NULL) { 
			stack.push(curr_->left_);
		}
		if (curr_->right_ != NULL) {
			stack.push(curr_->right_);
		}	
		if (stack.empty()) {curr_ = NULL; }
		else { 
			curr_ = stack.top();
			while (!stack.empty() && curr_->data_ <= 0)
			{
				++(*this);
			}
		}
	}

	return *this;
}

                    // if (!traversal->empty()) {
                    //     current = traversal->pop();			
                    //     if(current->right != NULL) {
					// 		 current = current->right;
					// 		 while (current != NULL)
					// 		 {
					// 		   stack.push(current);
					// 		   current = current->left;
					// 		 }
        
      				// 	   }
                    //     current = traversal->peek();
                    // }	
                    // return *this;

template <class T>
T Tree<T>::Iterator::operator*() const {
	// TODO: your code here
	if (curr_ == NULL) { return T(); }
	return curr_->data_;
}



/*******************
 ** PROVIDED CODE **
 *******************/
template <class T>
bool Tree<T>::Iterator::operator!=(const Tree<T>::Iterator &other) {
	return !(curr_ == other.curr_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::begin() {
	return Iterator(root_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::end() {
	return Iterator(NULL);
}

#endif
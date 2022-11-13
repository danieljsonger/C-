/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next); // could be just tail_ here
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
  while (current != NULL){
      ListNode *temp = current->next;
      delete current;
      current = temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }

  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;

  if(tail_ != NULL){
    tail_->next = newNode;
  }

  if(head_ == NULL){
    head_ = newNode;
  }

  tail_ = newNode; 
  length_++;
  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr->next != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1

  ListNode * curr = this->head_;
  while (curr != NULL)
  {

    if(curr->next != NULL){
      if(curr->next->next != NULL){
        if(curr->next->next->next != NULL){
          if(curr != this->head_){
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
          } else {
            curr->next->prev = NULL;
            this->head_ = curr->next;
          }
          curr->prev = curr->next->next; 
          curr->next = curr->next->next->next;
          curr->prev->next = curr;
          curr->next->prev = curr;
        } else {
          if(curr != this->head_){
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
          } else {
            curr->next->prev = NULL;
            this->head_ = curr->next;
          }
          curr->prev = curr->next->next; 
          curr->next = NULL;
          curr->prev->next = curr;
        }
      }
    }
    curr = curr->next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if (startPoint == endPoint) return; 
  if ((startPoint == NULL) || (endPoint == NULL)) return;

  ListNode * startPrev = startPoint->prev;
  ListNode * endNext = endPoint->next;

  ListNode * curr = startPoint;
  ListNode * tempPrev;

  while (curr != NULL && curr != endNext)
  {
    tempPrev = curr->prev;
    curr->prev = curr->next;
    curr->next = tempPrev;
    curr = curr->prev;
  }

  endPoint->prev = startPrev;
  startPoint->next = endNext;

  if (startPrev != NULL) { startPrev->next = endPoint; }
  if (endNext != NULL) { endNext->prev = startPoint; }

  ListNode * temp = endPoint;
  endPoint = startPoint;
  startPoint = temp;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  // if(n == 0 || n == 1) return;

  // ListNode * temp = head_;
  // ListNode * start = temp;
  // ListNode * finish  = NULL;
  // int count = n;
  // while(temp != NULL){
  //   if(count == 0){
  //     count = n;
  //     reverse(start, finish);

  //     start = temp;
  //     finish = temp;
  //   }
  //    if(temp->next == NULL){
  //     return;
  //   } 
  //   finish = temp;
  //   temp = temp -> next;
  //   count--;
  // }
  if(n <= 0 || n == 1) return;
  if(n >= length_) { this->reverse(); return; }

  ListNode * curr = this->head_;
  ListNode * start = curr;
  int count = 0;

  while (count < length_)
  {
    curr = start;
    for(int i = 0; i < n-1 && curr->next != NULL; i++){
      curr = curr->next;
    }

    // if (curr->next == NULL){ break; }

    reverse(start,curr);

    if(count == 0) { head_ = start; }
    count += n;
    if (curr->next != NULL) { start = curr->next; }
    else { break; }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
    if (first == NULL)
  {
    return second;
  }
  else if (second == NULL)
  {
    return first;
  }
  ListNode *start = NULL;

  ListNode *temp1 = first;
  ListNode *temp2 = second;
  if (temp1->data < temp2->data)
  {
    ListNode *temp = temp1->next;
    temp1->prev = NULL;
    temp1->next = NULL;
    start = temp1;
    temp1 = temp;
  }
  else
  {
    ListNode *temp = temp2->next;
    temp2->prev = NULL;
    temp2->next = NULL;
    start = temp2;
    temp2 = temp;
  }
  ListNode *curr = start;

  while (temp1 != NULL || temp2 != NULL)
  {
    if (temp1 != NULL && temp2 != NULL)
    {
      if (temp1->data < temp2->data)
      {
        ListNode *temp = temp1->next;
        temp1->prev = NULL;
        temp1->next = NULL;
        curr->next = temp1;
        temp1->prev = curr;
        temp1 = temp;
        curr = curr->next;
      }
      else
      {
        ListNode *temp = temp2->next;
        temp2->prev = NULL;
        temp2->next = NULL;
        curr->next = temp2;
        temp2->prev = curr;
        temp2 = temp;
        curr = curr->next;
      }
    }
    else if (temp1 == NULL)
    {
      ListNode *temp = temp2->next;
      temp2->prev = NULL;
      temp2->next = NULL;
      curr->next = temp2;
      temp2->prev = curr;
      temp2 = temp;
      curr = curr->next;
    }
    else
    {
      ListNode *temp = temp1->next;
      temp1->prev = NULL;
      temp1->next = NULL;
      curr->next = temp1;
      temp1->prev = curr;
      temp1 = temp;
      curr = curr->next;
    }
  }
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1 || start == NULL)
  {
    return start;
  }
  int half = chainLength / 2;
  ListNode *middle = split(start, half);
  ListNode *left = start;

  ListNode *new_left = mergesort(left, half);
  ListNode *new_right = mergesort(middle, chainLength - half);
  ListNode *new_head = merge(new_left, new_right);
  /// @todo Graded in MP3.2
  return new_head;
}

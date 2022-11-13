#include "binarytree.h"
#include <iostream>
#include <cstdlib>

const string RED_TEXT = "\033[1;31m";
const string GREEN_TEXT = "\033[1;32m";
const string RESET_TEXT = "\033[0m";

void print_pass(string message) {
  cout<<GREEN_TEXT<<"TEST PASSED"<<RESET_TEXT<<": "<<message<<endl;
}

void print_fail(string message) {
  cout<<RED_TEXT<<"TEST FAILED"<<RESET_TEXT<<": "<<message<<endl;
  exit(1);
}


int main() {
  srand(225);
  int ct;

  // Example #1
  BinaryTree<int> t1;
  t1.insert(4);
  t1.insert(3);
  t1.insert(5);

  ct = t1.countLeafNodes();
  if (ct == 2) { print_pass("Example #1 passed (count == 2)"); }
  else {
    cout<<"Returned value: "<<ct<<endl;
    cout<<"Expected: 2"<<endl;
    print_fail("Example #1 failed (count != 2)");
  }


  // Example #2
  BinaryTree<int> t2;
  t2.insert(3);
  t2.insert(1);
  t2.insert(5);
  t2.insert(4);

  ct = t2.countLeafNodes();
  if (ct == 2) { print_pass("Example #2 passed (count == 2)"); }
  else {
    cout<<"Returned value: "<<ct<<endl;
    cout<<"Expected: 2"<<endl;
    print_fail("Example #2 failed (count != 2)");
  }


  return 0;
}

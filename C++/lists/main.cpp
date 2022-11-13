#include "List.h"

using namespace std;

int main() {

  List<int> myList;

  myList.insertBack(1);
  myList.insertBack(2);
  myList.insertBack(3);
  myList.insertBack(4);
  myList.insertBack(5);
  myList.insertBack(6);
  myList.insertBack(7);
  myList.insertBack(8);
  myList.insertBack(9);
  myList.insertBack(10);
  
  
  myList.print();
  cout << endl;

  myList.reverseNth(6);
  myList.print();
  cout << endl;

  return 0;
}

#include <iostream>

#include "LinkedList.h"
using namespace std;

int main() {
  LinkedList mylist;
  mylist.add("Andy");
  mylist.add("Bobo");
  mylist.add("Chuck");
  mylist.add("Drogo");
  mylist.add("Erin");
  mylist.add("Frodo");

  cout << mylist.get(0) << endl;

  system("pause");
  return 0;
}

#include <iostream>
#include <string>

using namespace std;

class Node {
 private:
  string data;
  Node *next;

 public:
  Node();
  Node(string data, Node *next);
  ~Node();
  string getData();
  void setData(string newData);
  Node *getNext();
  void setNext(Node *newNext);
};

Node::Node() {
  this->data = "";
  this->next = NULL;
}

Node::Node(string data, Node *next) {
  this->data = data;
  this->next = next;
}

Node::~Node() {}

string Node::getData() { return data; }
void Node::setData(string newData) { data = newData; }
Node *Node::getNext() { return next; }
void Node::setNext(Node *newNext) { next = newNext; }

class LinkedList {
 private:
  Node *head;

 public:
  LinkedList();
  ~LinkedList();
  void add(string s);                // to add node
  void remove(string s);             // to remove node
  void display();                    // to display data
  void set(int index, string data);  // to set node by its index
  Node *getNode(int index);          // to get node by its index
  string get(int index);             // to get data by its index
  int size();                        // to get size
};
LinkedList::LinkedList() { head = nullptr; }
LinkedList::~LinkedList() {}

void LinkedList::add(string s) {
  if (head == nullptr) {  // checking if Node is created
    head = new Node(s, nullptr);
  } else {
    Node *temp = new Node(s, head);  // creating node
    head = temp;
  }
}
void LinkedList::remove(string s) {
  Node *node = head;
  Node *prev = nullptr;
  while (node != nullptr) {  // loop for finding node
    if (node->getData() == s) {
      if (prev == nullptr) {
        head = head->getNext();
        delete node;
      } else {
        prev->setNext(node->getNext());
        delete node;  // removing node
      }
      break;
    }
    prev = node;
    node = node->getNext();
  }
}

string LinkedList::get(int index) {
  Node *current = this->head;
  int count = 0;
  while (current != NULL) {
    if (count == index) return current->getData();
    count++;
    current = current->getNext();
  }
  // return null if this element is not found
  return NULL;
}

Node *LinkedList::getNode(int index) {
  Node *current = this->head;
  int count = 0;
  while (current != NULL) {
    if (count == index) return current;
    count++;
    current = current->getNext();
  }

  // returns null if this element is not found
  return NULL;
}

void LinkedList::set(int index, string data) {
  this->getNode(index)->setData(data);
}

int LinkedList::size() {
  Node *current = this->head;
  int size = 0;
  while (current != NULL) {
    size++;
    current = current->getNext();
  }
  return size;
}

void LinkedList::display() {
  Node *temp = head;
  while (temp != nullptr) {           // loop over the list
    cout << temp->getData() << endl;  // displaying each data
    temp = temp->getNext();
  }
  cout << endl;
}
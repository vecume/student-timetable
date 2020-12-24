#include <string>
using namespace std;

class Student {
 public:
  Student();
  ~Student(){};
  void setFullName(string fullname);
  void setID(string ID);
  void setGroupNumber(string groupNumber);
  void setPassword(string password);
  string getPassword();
  string getFullName();
  string getID();
  string getGroupNumber();

  friend void operator<<(ostream &out, Student &s);

 private:
  string fullName;
  string ID;
  string groupNumber;
  string password;
};

Student::Student() {
  fullName = "undefined";
  ID = "undefined";
  groupNumber = "undefined";
  password = "Iut2020";
}

void Student::setPassword(string password) { this->password = password; }
void Student::setFullName(string fullName) { this->fullName = fullName; }
void Student::setID(string ID) { this->ID = ID; }
void Student::setGroupNumber(string groupNumber) {
  this->groupNumber = groupNumber;
}
string Student::getPassword() { return password; }
string Student::getFullName() { return fullName; }
string Student::getID() { return ID; }
string Student::getGroupNumber() { return groupNumber; }

void operator<<(ostream &out, Student &s) {
  out << "\n\t\tFULL NAME: " << s.fullName << endl;
  out << "\t\tGROUP: " << s.groupNumber << endl;
  out << "\t\tID: " << s.ID << endl;
}
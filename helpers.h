#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "LinkedList.h"
#include "Student.h"
#include "TimeTableVariables.h"

using namespace std;
LinkedList split(string s, char c) {  // returns an array
  LinkedList splittedData;
  string::size_type i = 0;
  string::size_type j = s.find(c);

  while (j != string::npos) {
    splittedData.add(s.substr(i, j - i));
    i = ++j;
    j = s.find(c, j);

    if (j == string::npos) splittedData.add(s.substr(i, s.length()));
  }
  return splittedData;
}

Student searchById(string id, LinkedList data) {
  Student s;
  id = "U" + id;
  for (int i = 0; i < data.size(); i++) {
    LinkedList oneLine = split(data.get(i), ',');
    if (id == oneLine.get(3)) {
      s.setID(oneLine.get(3));
      s.setFullName(oneLine.get(2));
      s.setGroupNumber(oneLine.get(1));
      s.setPassword(oneLine.get(0));
    }
  }
  return s;
}

void showTimeTable(Student &s) {
  LinkedList temp = split(s.getGroupNumber(), '-');
  LinkedList groupsTimetable = getTimetable();
  int length = groupsTimetable.size();
  int groupIndex = stoi(temp.get(0));
  cout << "\t\t\t\t" << groupsTimetable.get(length - groupIndex) << endl;
}

void changePassword(Student &s) {
  while (true) {
    string line;
    string newPassword;
    string tempPassword;
    cout << "\tIF YOU WANT TO EXIT ENTER DOT(.)" << endl;
    cout << "\n\tENTER YOUR OLD PASSWORD: ";
    cin >> tempPassword;
    system("cls");
    if (tempPassword == ".") {
      break;
    }
    if (s.getPassword() == tempPassword) {
      cout << "\n\tNOW, ENTER NEW PASSWORD: ";
      cin >> newPassword;
      cout << "\tNew PASSWORD SAVED" << endl;
      s.setPassword(newPassword);
      ifstream myfile("StudentData.txt");
      LinkedList database;

      if (myfile.is_open()) {
        while (getline(myfile, line)) {
          database.add(line);
        }
      }
      for (int i = 0; i < database.size(); i++) {
        LinkedList oneLine = split(database.get(i), ',');
        if (s.getID() == oneLine.get(3)) {
          string newData = oneLine.get(3) + "," + oneLine.get(2) + "," +
                           oneLine.get(1) + "," + newPassword;
          database.set(i, newData);
          cout << database.get(i) << endl;
        }
      }
      ofstream newFile;
      newFile.open("StudentData.txt");
      if (newFile.is_open()) {
        for (int i = 0; i < database.size(); i++) {
          newFile << database.get(i) << "\n";
        }
        newFile.close();
      }
      break;
    } else {
      cout << "\n\tWRONG PASSWORD!!!" << endl;
    }
  }
}

void accountMenu(Student &s) {
  bool exit = false;
  while (!exit) {
    cout << "\n\n\t\t\t--- ACCOUNT MENU ---" << endl;
    cout << "\t1. SEE TIMETABLE" << endl;
    cout << "\t2. CHANGE PASSWORD" << endl;
    cout << "\t3. SEE ACCOUNT INFO" << endl;
    cout << "\t4. LOG OUT" << endl;
    int choice;
    cout << "\n\tEnter your choice: ";
    cin >> choice;
    system("cls");
    switch (choice) {
      case 1:
        showTimeTable(s);
        break;
      case 2:
        changePassword(s);
        break;
      case 3:
        cout << s;
        break;
      case 4:
        exit = true;
        break;
      default:
        cout << "\n\n\t\tI N V A L I D   C H O I C E" << endl;
        break;
    }
  }
}

void getInfoAboutAnyStudent() {
  ifstream myfile("StudentData.txt");
  LinkedList database;  // temporary array to store students data from file
  string line;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      database.add(line);  // pushing data to array
    }
  }
  while (true) {
    string id;
    cout << "\n\n\tENTER DOT(.) to EXIT ";
    cout << "\n\n\tPLEASE ENTER your ID:   U";
    cin >> id;
    system("cls");
    if (id == ".") {
      break;
    }
    string password;
    Student s;
    s = searchById(id,
                   database);  // searching student and returning Student object
    if (s.getFullName() != "undefined")  // check if student found
    {
      cout << s;
    } else {
      cout << "\n\n\tSTUDENT WITH SUCH ID NOT FOUND!!!" << endl;
    }
  }
}

void logIn() {
  while (true) {
    ifstream myfile("StudentData.txt");
    LinkedList database;  // temporary array to store students data from
                          // file
    string line;

    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        database.add(line);  // pushing data to array
      }
    }
    string id;
    cout << "\n\n\tENTER DOT(.) to EXIT" << endl;
    cout << "\tPLEASE ENTER your ID:   U";
    cin >> id;
    system("cls");
    if (id == ".") {
      break;
    }
    string password;
    Student s;
    s = searchById(id,
                   database);  // searching student and returning Student object
    if (s.getFullName() != "undefined")  // check if student found
    {
      cout << "\tYOUR ID: " << s.getID();
      cout << "\n\n\tPlease enter your password to enter your account: ";
      cin >> password;
      if (s.getPassword() == password) {
        /// MENU

        accountMenu(s);
      } else {
        cout << "\n\n\tWRONG PASSWORD!!!\n\tTry Again!!!" << endl;
      }
    } else {
      cout << "\n\n\tACCOUNT WITH SUCH ID NOT FOUND!!!" << endl;
    }
  }
}

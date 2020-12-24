#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Class.h"
#include "TimeTableVariables.h"

using namespace std;
vector<string> split(string s, char c) {  // returns an array
  vector<string> temp;
  string::size_type i = 0;
  string::size_type j = s.find(c);

  while (j != string::npos) {
    temp.push_back(s.substr(i, j - i));
    i = ++j;
    j = s.find(c, j);

    if (j == string::npos) temp.push_back(s.substr(i, s.length()));
  }
  return temp;
}

Student searchById(string id, vector<string> data) {
  Student s;

  id = "U" + id;
  bool isFound = false;
  for (int i = 0; i < data.size(); i++) {
    vector<string> oneLine = split(data[i], ',');
    if (id == oneLine[0]) {
      s.setID(oneLine[0]);
      s.setFullName(oneLine[1]);
      s.setGroupNumber(oneLine[2]);
      s.setPassword(oneLine[3]);
      isFound = true;
      return s;
    }
  }
  return s;
}

void showTimeTable(Student& s) {
  vector<string> temp = split(s.getGroupNumber(), '-');
  int groupIndex = stoi(temp[2]) - 1;
  cout << "\t\t\t\t" << groupsTimetable[groupIndex] << endl;
}

void changePassword(Student& s) {
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
      ifstream myfile("Text.txt");
      vector<string> database;

      if (myfile.is_open()) {
        while (getline(myfile, line)) {
          database.push_back(line);
        }
      }
      for (int i = 0; i < database.size(); i++) {
        vector<string> oneLine = split(database[i], ',');
        if (s.getID() == oneLine[0]) {
          oneLine[3] = newPassword;
          database[i] = oneLine[0] + "," + oneLine[1] + "," + oneLine[2] + "," +
                        oneLine[3];
        }
      }
      ofstream newFile;
      newFile.open("Text.txt");
      if (newFile.is_open()) {
        for (int count = 0; count < database.size(); count++) {
          newFile << database[count] << "\n";
        }
        newFile.close();
      }
      break;
    } else {
      cout << "\n\tWRONG PASSWORD!!!" << endl;
    }
  }
}

void accountMenu(Student& s) {
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
  ifstream myfile("Text.txt");
  vector<string> database;  // temporary array to store students data from file
  string line;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      database.push_back(line);  // pushing data to array
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
    ifstream myfile("Text.txt");
    vector<string> database;  // temporary array to store students data from
                              // file
    string line;

    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        database.push_back(line);  // pushing data to array
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

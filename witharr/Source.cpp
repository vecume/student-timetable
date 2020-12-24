#include "helpers.h"
using namespace std;

int main() {
	bool exit = false;
	while (!exit)
	{
		cout << "\t\t\t\tS T U D E N T   T I M E T A B LE" << endl;
		cout << "\n\t\t ---MENU---";
		cout << "\n\t1. LOG IN" << endl;
		cout << "\t2. GET INFO ABOUT ANY STUDENT" << endl;
		cout << "\t0. EXIT" << endl;
		int choice;
		cout << "\n\tEnter your choice: ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			logIn();
			break;
		case 2:
			getInfoAboutAnyStudent();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\n\n\t\tI N V A L I D   C H O I C E" << endl;
			break;
		}
	}
	return 0;
}


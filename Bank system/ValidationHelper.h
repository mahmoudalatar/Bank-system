#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27
#define KEY_ENTER 13


class ValidationHelper
{
public:
	static bool ValidateName(string name) {
		//Reg Exp [a-z , A-Z] or :
		string pattern = " 0123456789~!@#$%^&*()_+=?<>,.;:";
		for (int i = 0; i < name.size(); i++) {
			if (pattern.find(name[i]) >= 0 && pattern.find(name[i]) <= pattern.size() || name.size() < 5 || name.size() > 20) {
				return false;
			}
		}
		return true;
	}

	static bool ValidatePassword(string password) {
		//Reg Exp [a-z , A-Z] or :
		for (int i = 0; i < password.size(); i++) {
			if (password[i] == ' ' || password.size() < 8 || password.size() > 20) {
				return false;
			}
		}
		return true;
	}

	//To center the title
	static void centerTitle(string title) {
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		if (title != " ") {
			//change title color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 151);
			cout << "\t" << title << endl << endl << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else {
			cout << "\t" << endl << endl << endl;
		}
	}

	//to center the text
	static string tabcenter() {
		return "\t";
	}

	//Display function
	static  int menu(string menu[], int num, string title = " ") {
		bool active = true;
		int pointer = 0;

		while (active)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			centerTitle(title);

			for (int i = 0; i < num; i++) {
				if (i == pointer) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << tabcenter() << menu[i] << endl;
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << tabcenter() << menu[i] << endl;
				}
			}

			while (active) {
				int key = _getch();
				if (key == 72) {
					if (pointer <= 0) {
						pointer = num - 1;
						break;
					}
					pointer--;
					break;
				}
				else if (key == 80) {
					if (pointer == num - 1) {
						pointer = 0;
						break;
					}
					pointer++;
					break;
				}
				else if (key == 27 || key == 8) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					active = false;
					return 100;
				}
				else if (key == 13) {
					//to solve the last choise green color
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					return pointer + 1;
				}
			}
		}
	}

	//Show and Check Name and password
	static vector<string> signUpScreen() {
		bool b;
		string name, password;
		vector <string> v;

		do {
			system("cls");
			centerTitle("Sign Up");
			cout << tabcenter() << "Please enter name" << endl << endl;
			cout << tabcenter() << "| ";
			cin >> name;

			if (!ValidateName(name) || name.size() < 5 && name.size() > 20) {
				cout << tabcenter() << "please Enter the name in the correct alphabetic chars and correct range from 5 to 20 characters." << endl << endl;
				b = true;
				int key = _getch();
				if (key == 27) {
					v.clear();
					return v;
				}
			}
			else {
				b = false;
				v.push_back(name);
			}
			if (!b) {
				cout << endl << tabcenter() << "please Enter your password" << endl << endl;
				cout << tabcenter() << "| ";
				cin >> password;

				if (!ValidatePassword(password)) {
					cout << tabcenter() << "please Enter password in the correct range from 8 to 20 characters and wihtout spaces." << endl;
					b = true;
					int key = _getch();
					if (key == 27) {
						v.clear();
						return v;
					}
				}
				else {
					b = false;
					v.push_back(password);
				}
			}
		} while (b);
		return v;
	}

	//check id
	static bool checkIsint(string id) {
		//if the id not intger or wroing it ill not contuning the rest of the code.
		for (int i = 0; i < id.length(); i++) {
			if (isdigit(id[i]) == false) {				
				return false;
			}
			else {
				return true;
			}			
		}
	}

	static string updatePassword() {
		string password;

		system("cls");
		centerTitle("Update Password");
		cout << endl << tabcenter() << "please Enter new password" << endl << endl;
		cout << tabcenter() << "| ";
		cin >> password;

		if (!ValidatePassword(password)) {
			cout << tabcenter() << "please Enter password in the correct range from 8 to 20 characters and wihtout spaces." << endl;
			_getch();
			return "0";
		}
		else {
			cout << tabcenter() << "password is update successfully." << endl;
			_getch();
			return password;
		}
	}

	static string changeName() {
		string name;

		system("cls");
		centerTitle("Change name");
		cout << tabcenter() << "Please enter name" << endl << endl;
		cout << tabcenter() << "| ";
		cin >> name;

		if (!ValidateName(name) || name.size() < 5 && name.size() > 20) {
			cout << tabcenter() << "please Enter the name in the correct alphabetic chars and correct range from 5 to 20 characters." << endl << endl;
			_getch();
			return "nall";
		}
		else {
			return name;
		}
	}
};


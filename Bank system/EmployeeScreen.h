#include <iostream>
#include <string>
#include <Windows.h>
#include "Parent.h"
#include <conio.h>
#include <fstream>
#include "Client.h"
#include "Files.h"
#include "ValidationHelper.h"
#include "ClientScreen.h"

using namespace std;
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#pragma comment(lib, "user32")
#pragma once


class EmployeeScreen
{
public:
	static void signUpEmployee() {
		vector<string> v;
		Employee c;

		v = ValidationHelper::signUpScreen();
		if (!v.empty()) {
			c.setName(v[0]);
			c.setPassword(v[1]);
			Files::addEmployee(c);
			cout << ValidationHelper::tabcenter() << "Account created." << endl;
			_getch();
		}
	}

	//Log In Employee Screen
	static vector<string> logInEmployee() {
		vector<string> info;
		vector <Employee> v = Files::getAllEmployees();
		string password, error = "", id;
		int id2, counter = 0;
		bool b = true, isInt;

		do {
			system("cls");
			ValidationHelper::centerTitle("Log In");
			info.clear();
			info.push_back("employee");

			//ID
			cout << ValidationHelper::tabcenter() << "Enter your Id" << endl;
			cout << ValidationHelper::tabcenter() << "| ";
			cin >> id;

			isInt = ValidationHelper::checkIsint(id);
			if (isInt) {
				id2 = stoi(id);
				//Password
				cout << endl << ValidationHelper::tabcenter() << "Enter your Password" << endl;
				cout << ValidationHelper::tabcenter() << "| ";
				cin >> password;

				for (int i = 0; i < v.size(); i++) {
					if (password == v[i].getPassword() && id2 == v[i].getId()) {
						b = false;
						info.push_back(to_string(id2));
						info.push_back(password);
						error = "";
						break;
					}
					else {
						b = true;
						error = "Password or Id is wrong.";
					}
				}
			}
			else {
				error = "please Enter the id in numbers only.";
			}
			if (error != "") {
				cout << ValidationHelper::tabcenter() << error << endl << endl;
				cout << ValidationHelper::tabcenter() << "presse any key to continue or esc to go back." << endl << endl;
				int key = _getch();
				if (key == 27 || key == 8) {
					info.clear();
					return info;
				}
			}
		} while (b);
		return info;
	}

	//show account
	static void showAccount(vector<string> info) {
		string mainMenu[6] = { "1: Display myInfo\n","2: Update password\n","3: Add new Client\n", "4: Search for Client\n", "5: Show all clients\n", "6: Logout\n" };

		while (true) {
			int id = stoi(info[1]);
			int p = ValidationHelper::menu(mainMenu, 6, Files::getEmployee(id).getName() + " Account");

			switch (p) {
			case 1:
				system("cls");
				ValidationHelper::centerTitle("Account information");
				Files::getEmployee(id).display();
				_getch();
				break;
			case 2:
				updateEmployeePassword(id);
				break;
			case 3:
				ClientScreen::signUpClient();
				break;
			case 4:
				searchClient();
				break;
			case 5:
				showAllClients();
				break;
			case 6:
				exit(0);
				break;
			case 100:
				exit(0);
				break;
			}
		}
	}

	//update password
	static void  updateEmployeePassword(int id) {
		string password = ValidationHelper::updatePassword();
		if (password != "0") {
			Files::changeEmployeeInfo(id, "password", password);
		}
	}

	static void searchClient() {
		string id;
		bool num;
		system("cls");
		ValidationHelper::centerTitle("Client Information");
		cout << ValidationHelper::tabcenter() << "Enter Client Id" << endl << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> id;
		num = ValidationHelper::checkIsint(id);
		Client client = Files::getClient(stoi(id));

		if (client.getName() == "nothing") {
			cout << ValidationHelper::tabcenter() << "There is no Client match to this id" << endl << endl;
			_getch();
		}
		else {
			string title = " #" + to_string(client.getId()) + " Information ";			
			changeClientInfo(client.getId(), title);
			cout << ValidationHelper::tabcenter() << "Information updated" << endl;
			_getch();
		}
	}

	static void showAllClients() {
		vector<Client> clients = Files::getAllClients();
		string* names = new string[clients.size()];

		for (int i = 0; i < clients.size(); i++) {
			names[i] = to_string(i+1) + ": Name: " + clients[i].getName() + " - Id: " + to_string(clients[i].getId());
		}

		int p = ValidationHelper::menu(names, clients.size());
		delete[] names;
		for (int i = 0; i < clients.size(); i++) {
			if (p == clients[i].getId()) {
				Client client = Files::getClient(p);

				if (client.getName() == "nothing") {
					cout << ValidationHelper::tabcenter() << "There is no Client match to this id" << endl << endl;
					_getch();
				}
				else {
					string title = " #" + to_string(client.getId()) + " Information ";
					changeClientInfo(client.getId(), title);
				}
			}
		}
		
	}

	static int changeClientInfo(int id, string title) {
		string name;
		string editClientInfo[7] = { "1: display Info\n", "2: Change name\n","3: Update password\n","4: Deposit\n", "5: Withdraw\n", "6: Transfer money\n", "7: Back\n" };

		while (true) {
			int p = ValidationHelper::menu(editClientInfo, 7, Files::getClient(id).getName() + title);

			switch (p) {
			case 1:
				system("cls");
				ValidationHelper::centerTitle("Account information");
				Files::getClient(id).display();
				_getch();
				break;
			case 2:
				name = ValidationHelper::changeName();
				Files::changeClientInfo(id, "name", name);
				break;
			case 3:
				ClientScreen::updateClientPassword(id);
				break;
			case 4:
				ClientScreen::deposit(id);
				break;
			case 5:
				ClientScreen::withdraw(id);
				break;
			case 6:
				ClientScreen::transfer(id);
				break;
			case 7:
				return 0;
				break;
			case 100:
				return 0;
				break;
			}
		}
	}
};


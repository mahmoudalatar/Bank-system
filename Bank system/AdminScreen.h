#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "Parent.h"
#include "Client.h"
#include "Files.h"
#include "ValidationHelper.h"
#include "Parser.h"
#include "ClientScreen.h"
#include "EmployeeScreen.h"

using namespace std;
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#pragma comment(lib, "user32")
#pragma once


class AdminScreen
{
public:
	static void signUpAdmin() {
		vector<string> v;
		Employee c;
		v = ValidationHelper::signUpScreen();

		if (!v.empty()) {
			c.setName(v[0]);
			c.setPassword(v[1]);
			ifstream f;
			f.open("admins.txt", ios::in);
			string s;
			f >> s;
			f.close();
			if (s == "") {
				Files::addAdmin(c);
				cout << ValidationHelper::tabcenter() << "Account created." << endl;
				_getch();
			}
			else {
				cout << ValidationHelper::tabcenter() << "There is only one Admin accounte." << endl;
				_getch();
			}
		}
	}

	//Log In Admin Screen
	static vector<string> logInAdmin() {
		vector<string> info;
		vector <Employee> v = Files::getAllAdmins();
		string password, error = "", id;
		int id2, counter = 0;
		bool b = true, isInt;

		do {
			system("cls");
			ValidationHelper::centerTitle("Log In");
			info.clear();
			info.push_back("admin");

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
		string mainMenu[9] = { "1: Display myInfo\n","2: Update password\n","3: Add new Client\n", "4: Search for Client\n", "5: Show all clients\n", "6: Add new Employee\n", "7: Search for employee\n","8: Show all employees\n", "9: Logout\n" };

		while (true) {
			int p = ValidationHelper::menu(mainMenu, 9, Files::getEmployee(stoi(info[1])).getName() + " Account");

			switch (p) {
			case 1:
				system("cls");
				ValidationHelper::centerTitle("Account information");
				Files::getAdmin(stoi(info[1])).display();
				_getch();
				break;
			case 2:
				updateAdminPassword(info);
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
				EmployeeScreen::signUpEmployee();
				break;
			case 7:
				searchEmployee();
				break;
			case 8:
				showAllEmployees();
				break;
			case 9:
				exit(0);
				break;
			case 100:
				exit(0);
				break;
			}
		}
	}

	//update password
	static void  updateAdminPassword(vector<string>info) {
		string password = ValidationHelper::updatePassword();
		if (password != "0") {
			Files::changeAdminInfo(stoi(info[1]), "password", password);
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
			names[i] = to_string(i + 1) + ": Name: " + clients[i].getName() + " - Id: " + to_string(clients[i].getId());
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
					string title =  " #" + to_string(client.getId()) + " Information ";
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

	// Employee access
	static void searchEmployee() {
		string id;
		bool num;
		system("cls");
		ValidationHelper::centerTitle("Employee Information");
		cout << ValidationHelper::tabcenter() << "Enter Client Id" << endl << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> id;
		num = ValidationHelper::checkIsint(id);
		Employee employee = Files::getEmployee(stoi(id));

		if (employee.getName() == "nothing") {
			cout << ValidationHelper::tabcenter() << "There is no employee match to this id" << endl << endl;
			_getch();
		}
		else {
			string title = " #" + to_string(employee.getId()) + " Information ";
			changeEmployeeInfo(employee.getId(), title);
			cout << ValidationHelper::tabcenter() << "Information updated" << endl;
			_getch();
		}
	}

	static void showAllEmployees() {
		vector<Employee> employees = Files::getAllEmployees();
		string* names = new string[employees.size()];

		for (int i = 0; i < employees.size(); i++) {
			names[i] = to_string(i + 1) + ": Name: " + employees[i].getName() + " - Id: " + to_string(employees[i].getId());
		}

		int p = ValidationHelper::menu(names, employees.size());
		delete[] names;
		for (int i = 0; i < employees.size(); i++) {
			if (p == employees[i].getId()) {
				Client employee = Files::getClient(p);

				if (employee.getName() == "nothing") {
					cout << ValidationHelper::tabcenter() << "There is no Client match to this id" << endl << endl;
					_getch();
				}
				else {
					string title =  " #" + to_string(employee.getId()) + " Information ";
					changeEmployeeInfo(employee.getId(), title);
				}
			}
		}
	}

	static int changeEmployeeInfo(int id, string title) {
		string name;
		string editClientInfo[5] = { "1: display Info\n", "2: Change name\n","3: Update password\n","4: Change salary\n", "5: Back\n" };

		while (true) {
			int p = ValidationHelper::menu(editClientInfo, 5, Files::getEmployee(id).getName() + title);

			switch (p) {
			case 1:
				system("cls");
				ValidationHelper::centerTitle("Account information");
				Files::getEmployee(id).display();
				_getch();
				break;
			case 2:
				name = ValidationHelper::changeName();
				Files::changeEmployeeInfo(id, "name", name);
				break;
			case 3:
				EmployeeScreen::updateEmployeePassword(id);
				break;
			case 4:
				changeSalary(id);
				break;
			case 5:
				return 0;
				break;
			case 100:
				return 0;
				break;
			}
		}
	}

	static void changeSalary(int id) {
		string salary;
		bool isInt;

		system("cls");
		ValidationHelper::centerTitle("Change Salary");
		cout << ValidationHelper::tabcenter() << "Enter the new sallary" << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> salary;

		isInt = ValidationHelper::checkIsint(salary);
		if (isInt) {
			if (stod(salary) >= 5000) {
				cout << stod(salary) << endl;
				Files::changeEmployeeInfo(id, "salary", salary);
				cout << ValidationHelper::tabcenter() << "The salary is saved." << endl;
				_getch();
			}
			else {
				cout << ValidationHelper::tabcenter() << "The salary shoud be at less 5000." << endl;
				_getch();
			}
		}
	}
};


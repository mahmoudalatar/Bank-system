#include <iostream>
#include <string>
#include <Windows.h>
#include "Parent.h"
#include <conio.h>
#include <fstream>
#include "Client.h"
#include "Files.h"
#include "ValidationHelper.h"
using namespace std;
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#pragma once


class ClientScreen
{
public:
	//SignUp Client Screen
	static void signUpClient() {
		vector<string> v;
		Client c;

		v = ValidationHelper::signUpScreen();
		if (!v.empty()) {
			c.setName(v[0]);
			c.setPassword(v[1]);
			Files::addClient(c);
			cout << ValidationHelper::tabcenter() << "Account created." << endl;
			_getch();
		}
	}

	//Log In Client Screen
	static vector<string> logInClient() {
		vector<string> info;
		vector <Client> v = Files::getAllClients();
		string password, error = "", id;
		int id2, counter = 0;
		bool b = true, isInt;

		do {
			system("cls");
			ValidationHelper::centerTitle("Log In");
			info.clear();
			info.push_back("client");

			//ID
			cout << ValidationHelper::tabcenter() << "Enter your Id" << endl;
			cout << ValidationHelper::tabcenter() << "| ";
			cin >> id;

			isInt = ValidationHelper::checkIsint(id);
			if (isInt) {
				id2 = stoi(id);
				//Id and Password
				cout << endl << ValidationHelper::tabcenter() << "Enter your Password" << endl;
				cout << ValidationHelper::tabcenter() << "| ";
				cin >> password;

				for (int i = 0; i < v.size(); i++) {
					if (password == v[i].getPassword() && id2 == v[i].getId()) {
						b = false;
						info.push_back(to_string(id2));
						info.push_back(password);
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
		string mainMenu[6] = { "1: Display myInfo\n","2: Update password\n","3: Withdraw\n", "4: Deposit\n", "5: Transfer amount\n", "6: Logout\n" };

		while (true) {
			int id = stoi(info[1]);
			int p = ValidationHelper::menu(mainMenu, 6, Files::getClient(id).getName() + " Account");

			switch (p) {
			case 1:
				system("cls");
				ValidationHelper::centerTitle("Account information");
				Files::getClient(id).display();
				_getch();
				break;
			case 2:
				updateClientPassword(id);
				break;
			case 3:
				withdraw(id);
				break;
			case 4:
				deposit(id);
				break;
			case 5:
				transfer(id);
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
	static void updateClientPassword(int id) {
		string password = ValidationHelper::updatePassword();
		if (password != "0") {		
			Files::changeClientInfo(id, "password", password);
		}
	}

	//Withdraw
	static void withdraw(int id) {
		int money;
		Client c = Files::getClient(id);

		system("cls");
		ValidationHelper::centerTitle("Withdraw");
		cout << endl << ValidationHelper::tabcenter() << "please Enter the amount of the money you want to withdraw" << endl << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> money;

		if (money > c.getBalance()) {
			cout << ValidationHelper::tabcenter() << "the mount of money in your account is not enough." << endl;
			_getch();
		}
		else {
			cout << ValidationHelper::tabcenter() << "The money is being given to you now.";
			Files::changeClientInfo(id, "balance", to_string(c.getBalance() - money));
			_getch();
		}
	}

	//Deposit
	static void deposit(int id) {
		int money;
		Client c = Files::getClient(id);

		system("cls");
		ValidationHelper::centerTitle("Deposit");
		cout << endl << ValidationHelper::tabcenter() << "please Enter the amount of the money you want to deposit" << endl << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> money;

		if (money < 1500) {
			cout << ValidationHelper::tabcenter() << "The mount of money shoud at less to be 1500." << endl;
			_getch();
		}
		else {
			cout << ValidationHelper::tabcenter() << "The money saved in you account.";
			int i = c.getBalance() + money;
			Files::changeClientInfo(id, "balance", to_string(i));
			_getch();
		}
	}

	//Transfer amount
	static void transfer(int id) {
		Client c = Files::getClient(id);
		string otherClientId;
		int money;
		bool num;

		system("cls");
		ValidationHelper::centerTitle("Transfer Money");

		//ID
		cout << ValidationHelper::tabcenter() << "Enter Client Id" << endl << endl;
		cout << ValidationHelper::tabcenter() << "| ";
		cin >> otherClientId;
		num = ValidationHelper::checkIsint(otherClientId);

		if (!num) {
			cout << ValidationHelper::tabcenter() << "please Enter the id in numbers only." << endl << endl;
			_getch();
		}
		else {
			Client otherClient = Files::getClient(stoi(otherClientId));

			if (otherClient.getName() == "nothing") {
				cout << ValidationHelper::tabcenter() << "There is no Client match to this id" << endl << endl;
				_getch();
			}
			else {
				cout << endl << ValidationHelper::tabcenter() << "Enter the amount of money you want to transfer." << endl << endl;
				cout << ValidationHelper::tabcenter() << "| ";
				cin >> money;

				if (money > c.getBalance()) {
					cout << ValidationHelper::tabcenter() << "the mount of money in your account is not enough." << endl << endl;
					_getch();
				}
				else {
					cout << ValidationHelper::tabcenter() << "The money transferd to the client account.";
					//sending to the other client					
					int i = otherClient.getBalance() + money;
					Files::changeClientInfo(stoi(otherClientId), "balance", to_string(i));

					//change the balanc of the main clinet
					Files::changeClientInfo(id, "balance", to_string(c.getBalance() - money));
					_getch();
				}
			}
		}
	}
};


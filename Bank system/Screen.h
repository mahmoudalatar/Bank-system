#include <iostream>
#include <string>
#include <Windows.h>
#include "Parent.h"
#include <conio.h>
#include <fstream>
#include "Client.h"
#include "Files.h"
#include "ClientScreen.h"
#include "EmployeeScreen.h"
#include "AdminScreen.h"
#include "ValidationHelper.h"

using namespace std;

#pragma once
class Screen
{
public:

	//Login Menu
	static  void signUpMenu() {
		string lg[3] = { "1: Client\n","2: Employee\n", "3: Admin\n" };
		while (true)
		{
			int p = ValidationHelper::menu(lg, 3, "Sign Up");

			switch (p) {
			case 1:
				ClientScreen::signUpClient();
				break;
			case 2:
				EmployeeScreen::signUpEmployee();
				break;
			case 3:
				AdminScreen::signUpAdmin();
				break;
			case 100:
				menuSystem();
			}
		}

	}

	static vector<string> logInMenu() {
		string SM[3] = { "1: Client\n","2: Employee\n", "3: Admin"};
		vector<string> info;
		while (true)
		{
			int p = ValidationHelper::menu(SM, 3, "Log In");
			switch (p) {
			case 1:
				info = ClientScreen::logInClient();
				if (!info.empty()) {
					return info;
				}
				break;
			case 2:
				info = EmployeeScreen::logInEmployee();
				if (!info.empty()) {
					return info;
				}
				break;
			case 3:
				info = AdminScreen::logInAdmin();
				if (!info.empty()) {
					return info;
				}
				break;
			case 100:
				menuSystem();
			}
		}
	}

	//starting menu
	static vector<string> startMenu() {
		vector<string> info;
		string SM[2] = { "1: Sign UP\n","2: Log In\n" };
		int p = ValidationHelper::menu(SM, 2, "Main Menu");

		switch (p) {
		case 1:
			signUpMenu();
			break;
		case 2:
			info = logInMenu();
			return info;
			break;
		case 100:
			exit(0);
		}
	}

	static void menuSystem() {
		vector<string> info;

		//starting menu
		info = startMenu();

		// show account
		if (info[0] == "client") {
			ClientScreen::showAccount(info);
		}
		else if (info[0] == "employee") {
			EmployeeScreen::showAccount(info);
		}
		else if (info[0] == "admin") {
			AdminScreen::showAccount(info);
		}

	}
};


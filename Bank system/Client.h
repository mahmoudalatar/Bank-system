#pragma once
#include <iostream>
#include "Parent.h"
#include<fstream>
#include <string>
#include "ValidationHelper.h"

using namespace std;


class Client : public Parent
{
private:
	//Attributes:
	double balance;

public:
	//Constructors:
	Client() {
		this->balance = 0;
	}
	Client(string name, int id, string password, double balance) : Parent(name, id, password) {
		this->balance = balance;
	}

	//Setters
	void setBalance(double balance) {
		if (balance < 1500) {
			return;
		}
		this->balance = balance;
	}

	//Getters
	double getBalance() {
		return this->balance;
	}

	void display() {
		Parent::display();
		cout << ValidationHelper::tabcenter() << "Balance  = " << this->balance << endl;
	}
};

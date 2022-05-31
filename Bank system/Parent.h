#pragma once
#include <iostream>
#include<string>
#include<fstream>
#include "ValidationHelper.h"

using namespace std;


class Parent {
protected:
	//attre
	string name, password;
	int id;
public:
	//constructor
	Parent() {
		this->name = " ";
		this->id = 0;
		this->password = " ";
	}
	Parent(string name, int id, string password) {
		this->name = name;
		this->id = id;
		this->password = password;
	}
	//setter
	void setName(string name) {
		if (ValidationHelper::ValidateName(name)) {
			this->name = name;
		}
	}


	void setPassword(string password) {
		if (ValidationHelper::ValidatePassword(password)) {
			this->password = password;
		}
	}

	void setId(int id) {
		this->id = id;
	}
	void setBalance(double balance) {
		if (balance >= 1500)
			this->password = balance;
		else
			cout << "min balance is 1500." << endl;
	}
	//getter
	string getName() {
		return name;
	}
	string getPassword() {
		return password;
	}
	int getId() {
		return id;
	}
	void display() {
		cout << ValidationHelper::tabcenter() << "Name     = " << this->name << endl;
		cout << ValidationHelper::tabcenter() << "Id       = " << this->id << endl;
		cout << ValidationHelper::tabcenter() << "Password = " << this->password << endl;
	}


};


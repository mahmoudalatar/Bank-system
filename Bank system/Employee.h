#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Parent.h"
#include "ValidationHelper.h"

using namespace std;

class Employee : public Parent
{
private:
	//Attributes:
	double salary;
public:
	//Constructors:
	Employee() {
		this->salary = 0;
	}
	Employee(string name, int id, string password, double salary) : Parent(name, id, password) {
		this->salary = salary;
	}

	//Setters
	void setSalary(double salary) {
		if (salary < 5000) {
			return;
		}
		this->salary = salary;
	}

	//Getters
	double getSalary() {
		return this->salary;
	}

	void display() {
		Parent::display();
		cout << ValidationHelper::tabcenter() << "Salary   = " << this->salary << endl;
	}
};

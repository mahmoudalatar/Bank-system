#include "Client.h"
#include "Employee.h"
#include <vector>
#include <sstream>
using namespace std;

#pragma once
class Parser
{
public:

	static vector<string>split(string line) {
		vector<string>myVec;

		stringstream ss(line);
		string token;
		while (getline(ss, token, '#')) {
			myVec.push_back(token);
		}
		return myVec;
	}

	static Client parseToClient(string line) {
		vector<string>values = split(line);
		Client c;
		c.setId(stoi(values[0]));
		c.setName(values[1]);
		c.setPassword(values[2]);
		c.setBalance(stod(values[3]));
		return c;
	}

	static Employee parseToEmployee(string line) {
		vector<string>values = split(line);
		Employee obj;
		obj.setId(stoi(values[0]));
		obj.setName(values[1]);
		obj.setPassword(values[2]);
		obj.setSalary(stod(values[3]));
		return obj;
	}
};


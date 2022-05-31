#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Client.h"
#include "Employee.h"
#include "Parser.h"
using namespace std;
#pragma once


class Files
{
private:
	static int getLast(char* fileName) {
		ifstream file;
		file.open(fileName);
		int id;
		file >> id;
		file.close();
		return id;
	}

	static void saveLast(char* fileName, int id) {
		fstream file(fileName, ios::out);
		file << id;
		file.close();
	}

	static void saveEmployee(char* fileName, char* lastIdFile, Employee e) {
		int id = getLast(lastIdFile);
		fstream file(fileName, ios::app);
		if (e.getId() == 0) {
			file << id++ << "#" << e.getName() << "#" << e.getPassword() << "#" << e.getSalary() << "#" << "\n";
			saveLast(lastIdFile, id++);
		}
		else {
			file << e.getId()<< "#" << e.getName() << "#" << e.getPassword() << "#" << e.getSalary() << "#" << "\n";

		}
		file.close();
	}


public:
	//Change Info
	static void changeClientInfo(int id,string infoType, string data) {
		vector<Client> clients = Files::getAllClients();
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getId() == id) {
				if (infoType == "password") {
					clients[i].setPassword(data);
					break;
				}
				else if (infoType == "balance") {
					clients[i].setBalance(stoi(data));
					break;
				}
				else if (infoType == "name") {
					clients[i].setName(data);
					break;
				}
			}
		}
		Files::removeAllClients();
		for (int i = 0; i < clients.size(); i++) {
			Files::addClient(clients[i]);
		}
	}

	static void changeEmployeeInfo(int id, string infoType, string data) {
		vector<Employee> employees = Files::getAllEmployees();
		for (int i = 0; i < employees.size(); i++) {
			if (employees[i].getId() == id) {
				if (infoType == "password") {
					employees[i].setPassword(data);
					break;
				}
				else if (infoType == "balance") {
					employees[i].setBalance(stoi(data));
					break;
				}
				else if (infoType == "name") {
					employees[i].setName(data);
					break;
				}
				else if (infoType == "salary") {
					employees[i].setSalary(stod(data));
					break;
				}
			}
		}
		Files::removeAllEmployees();
		for (int i = 0; i < employees.size(); i++) {
			Files::addEmployee(employees[i]);
		}
	}

	static void changeAdminInfo(int id, string infoType, string data) {
		vector<Employee> employees = Files::getAllAdmins();
		for (int i = 0; i < employees.size(); i++) {
			if (employees[i].getId() == id) {
				if (infoType == "password") {
					employees[i].setPassword(data);
				}
				if (infoType == "balance") {
					employees[i].setBalance(stoi(data));
				}
			}
		}
		Files::removeAllAdmins();
		for (int i = 0; i < employees.size(); i++) {
			Files::addAdmin(employees[i]);
		}
	}

	//Add data
	static void addClient(Client c) {
		char clientId[] = "clientId.txt";
		int id = getLast(clientId);
		fstream file("clients.txt", ios::app);
		if (c.getId() == 0) {
			file << id++ << "#" << c.getName() << "#" << c.getPassword() << "#" << c.getBalance() << "\n";
			saveLast(clientId, id++);
		}
		else {
			file << c.getId() << "#" << c.getName() << "#" << c.getPassword() << "#" << c.getBalance() << "\n";
		}
		file.close();
	}

	static void addEmployee(Employee e) {
		char employees[] = "employees.txt";
		char employeeLastId[] = "employeeLastId.txt";
		saveEmployee(employees, employeeLastId, e);
	}

	static void addAdmin(Employee e) {
		char admins[] = "admins.txt";
		char adminLastId[] = "adminLastId.txt";
		saveEmployee(admins, adminLastId, e);
	}

	//Get data
	static Client getClient(int id) {
		vector <Client> v = Files::getAllClients();
		for (int i = 0; i < v.size(); i++) {
			if (id == v[i].getId()) {
				return v[i];
			}
		}
		Client c;
		c.setName("nothing");
		return c;
	}

	static Employee getEmployee(int id) {
		vector <Employee> v = Files::getAllEmployees();
		for (int i = 0; i < v.size(); i++) {
			if (id == v[i].getId()) {
				return v[i];
			}
		}
		Employee c;
		c.setName("nothing");
		return c;
	}	
	
	static Employee getAdmin(int id) {
		vector <Employee> v = Files::getAllAdmins();
		for (int i = 0; i < v.size(); i++) {
			if (id == v[i].getId()) {
				return v[i];
			}
		}
		Employee c;
		c.setName("nothing");
		return c;
	}

	//Get all data
	static vector<Client> getAllClients() {
		vector<Client>clients;
		fstream file;
		file.open("clients.txt", ios::in);
		string line;
		while (getline(file, line)) {
			Client c = Parser::parseToClient(line);
			clients.push_back(c);
		}
		file.close();
		return clients;
	}

	static vector<Employee>getAllEmployees() {
		vector<Employee>employees;
		fstream file;
		file.open("employees.txt", ios::in);
		string line;
		while (getline(file, line)) {
			Employee e = Parser::parseToEmployee(line);
			employees.push_back(e);
		}
		file.close();
		return employees;
	}

	static vector<Employee>getAllAdmins() {
		vector<Employee>employees;
		ifstream file;
		file.open("admins.txt");
		string line;
		while (getline(file, line)) {
			Employee e = Parser::parseToEmployee(line);
			employees.push_back(e);
		}
		file.close();
		return employees;
	}

	//Remove all
	static void removeAllClients() {
		fstream file;
		file.open("clients.txt", ios::out);
		file.close();
	}

	static void removeAllEmployees() {
		fstream file;
		file.open("employees.txt", ios::out);
		file.close();
	}

	static void removeAllAdmins() {
		fstream file;
		file.open("admins.txt", ios::out);
		file.close();
	}
		
};


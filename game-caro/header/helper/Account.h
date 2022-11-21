#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<fstream>
#include<vector>
class Account {
private:
	string acc;
	fstream ofs;
	//vector<string> account;
public:
	Account();
	void createAccount();
	string getAccount();

	//vector<string> getListAccount();
	void showAccount();
	int checkDuplicate();
	void addAccIntoList();
	int login(string account);
};

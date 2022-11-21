#include "Account.h"

Account::Account() {
	ofs.open("Account.ini", ios::app);
	ofs.close();
}
void Account::createAccount() {
	cout << "Create account: "; cin >> this->acc;
}
string Account::getAccount() {
	return this->acc;
}
//vector<string> Account::getListAccount() {
//	return this->account;
//}
void Account::showAccount() {

	string line;
	ofs.open("Account.ini", ios::in);
	while (!ofs.eof()) {
		getline(ofs, line);
		cout << line << endl;
	}
	ofs.close();

}
int Account::checkDuplicate() {
	string line;
	ofs.open("Account.ini", ios::in);
	while (!ofs.eof()) {
		getline(ofs, line);
		if (line == acc) {
			ofs.close();
			return 0;
		}
	}
	ofs.close();
	return 1;
}
void Account::addAccIntoList() {
	if (checkDuplicate() == 1) {
		ofs.open("Account.ini", ios::app);
		ofs << acc << endl;
		cout << "Account successfully created!!!" << endl;
		ofs.close();
	}
	else {
		cout << "The account has been used. Let's create another account." << endl;
	}
	ofs.open("Infor.ini", ios::app);
	ofs << acc << ' ' << 0 << ' ' << 0 << ' ' << 0; ofs.close();
	system("pause");
}
int Account::login(string account) {
	string line;
	ofs.open("Account.ini", ios::in);
	while (!ofs.eof()) {
		getline(ofs, line);
		if (line == account) {
			return 1;
		}
	}
	ofs.close();
	return 0;
}


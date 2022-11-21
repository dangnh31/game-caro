﻿#include "Controller.h"

int Controller::checkResult(const int& x, const int& y, const unsigned char& XO)
{
	if (x < view.getTableSize() && y < view.getTableSize())
	{
		int dem1, dem2, dem3, dem4, dem5, dem6, dem7, dem8, i = x, j = y;
		dem1 = dem2 = dem3 = dem4 = dem5 = dem6 = dem7 = dem8 = 0;
		while (j < view.getTableSize() && model.getBoard()[i][j].getCheck() == XO)
		{
			dem1++;
			j++;
			if (dem1 == 5)
			{
				return 1;
			}
		}
		i = x, j = y;
		while (j >= 0 && model.getBoard()[i][j].getCheck() == XO)
		{
			dem2++;
			j--;
			if (dem2 == 5)
			{
				return 1;
			}
		}
		//Kiểm tra đường ngang
		i = x, j = y;
		while (i < view.getTableSize() && model.getBoard()[i][j].getCheck() == XO)
		{
			dem3++;
			i++;
			if (dem3 == 5)
			{
				return 1;
			}
		}
		i = x, j = y;
		while (i >= 0 && model.getBoard()[i][j].getCheck() == XO)
		{
			dem4++;
			i--;
			if (dem4 == 5)
			{
				return 1;
			}
		}
		//Kiểm tra đường chéo chính
		i = x, j = y;
		while (i < view.getTableSize() && j < view.getTableSize() && model.getBoard()[i][j].getCheck() == XO)
		{
			dem5++;
			i++;
			j++;
			if (dem5 == 5)
			{
				return 1;
			}
		}

		i = x, j = y;
		while (i >= 0 && j >= 0 && model.getBoard()[i][j].getCheck() == XO)
		{
			dem6++;
			j--;
			i--;
			if (dem6 == 5)
			{
				return 1;
			}
		}
		//Kiểm tra đường chéo phụ
		i = x, j = y;
		while (i < view.getTableSize() && j >= 0 && model.getBoard()[i][j].getCheck() == XO)
		{
			dem7++;
			i++;
			j--;
			if (dem7 == 5)
			{
				return 1;
			}
		}

		i = x, j = y;
		while (i >= 0 && j < view.getTableSize() && model.getBoard()[i][j].getCheck() == XO)
		{
			dem8++;
			j++;
			i--;
			if (dem8 == 5)
			{
				return 1;
			}
		}
		return 0;
	}
}
void Controller::exportFile() {
	ofstream ofs("Infor.ini");
	for (int i = 0; i < model.Gettemp().size(); i++)
	{
		model.Gettemp()[i].ExportInfor(ofs);
	}
	ofs.close();
}
void Controller::import()
{
	model.Gettemp().clear();
	vector<string> lines;
	string line;
	ifstream ifs("Infor.ini", ios::in);
	if (!ifs.is_open()) {
		cerr << "Load data error!" << endl;
		return;
	}
	while (getline(ifs, line)) {
		lines.push_back(line);//Lưu từng dòng như một phần tử vào vector lines.
	}

	for (int i = 0; i < lines.size(); i++)
	{
		char str[25];
		char name[20];
		int win(0), lost(0), draw(0);
		strcpy_s(str, lines[i].c_str());
		sscanf_s(str, " %s  %d  %d  %d", name, 20, &win, &lost, &draw);
		unique_ptr<Player> temp(new Player);
		temp->setName(name);
		temp->setWinMatch(win);
		temp->setLoseMatch(lost);
		temp->setDrawMatch(lost);
		model.Gettemp().push_back(*temp);
		//cout << lines[i] << endl;
	}
	ifs.close();
}
void Controller::update(vector<Player>& temp)
{
	for (int i = 0; i < temp.size() - 1; i++)
	{
		for (int j = i + 1; j < temp.size(); j++)
		{
			if (temp[i].getName() == temp[j].getName())
			{
				temp[i].setWinMatch(temp[i].getWinMatch() + temp[j].getWinMatch());
				temp[i].setLoseMatch(temp[i].getLoseMatch() + temp[j].getLoseMatch());
				temp[i].setDrawMatch(temp[i].getDrawMatch() + temp[j].getDrawMatch());
				temp.erase(temp.begin() + j);
				j--;
			}
		}
	}
}

void Controller::showData() {
	fstream ifs;
	ifs.open("Infor.ini", ios::in);
	char name[25];
	char win[5];
	char lose[5];
	char draw[5];
	char account[25];
	cout << " \nEnter accout  : ";
	cin.ignore(100, '\n');
	cin.getline(account, 25);
	int x = 0;
	while (!ifs.eof())
	{

		ifs.getline(name, 25, ' ');
		ifs.getline(win, 5, ' ');
		ifs.getline(lose, 5, ' ');
		ifs.getline(draw, 5);
		if (strcmp(name, account) == 0)
		{

			cout << "\t\tInfo Player\n";
			cout << "Account: " << name << endl;
			cout << "Win: " << win << endl;
			cout << "Lose: " << lose << endl;
			cout << "Draw: " << draw << endl;
			x = 1;
			break;
		}
	}
	if (x == 0)
	{
		cout << " \n not found !!!!\n";
	}
	ifs.close();
}
void Controller::removeFile() {
	if (remove("Infor.ini") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
}
void Controller::ShowRePlay() {
	if (model.getCurentTurn() != 0) {
		system("cls");
		for (int i = 0; i < view.getTableSize() * 4 + 1; i++)
		{
			cout << '-';
		}
		cout << endl;
		for (int i = 0; i < view.getTableSize(); i++)
		{
			for (int j = 0; j < view.getTableSize(); j++)
			{
				cout << '|' << ' ' << ' ' << ' ';
			}
			cout << '|' << endl;
			for (int i = 0; i < view.getTableSize() * 4 + 1; i++)
			{
				cout << '-';
			}
			cout << endl;
		}
		//cout << model.getCurentTurn();
		for (int x = 1; x <= model.getCurentTurn(); x++) {
			for (int i = 0; i < model.getBoard().size(); i++) {
				for (int j = 0; j < model.getBoard().size(); j++) {
					if (x == model.getBoard()[i][j].getTurn()) {
						view.gotoXY(i * 4 + 2, j * 2 + 1);
						cout << model.getBoard()[i][j].getCheck();
						//cout << model.getBoard()[i][j].getTurn();
						Sleep(600);
					}
				}
			}
		}
		if (model.getCurentTurn() / 2 == 0) {
			view.gotoXY(0, 2 * view.getTableSize() + 2);
			cout << "O win" << endl;
		}
		else {
			view.gotoXY(0, 2 * view.getTableSize() + 2);
			cout << "X win" << endl;
		}
	}
	else { cout << "Not Match" << endl; }
	system("pause");
}
void Controller::Click(int x, int y, char& XO) {
	int m = x * 4 + 2;
	int n = y * 2 + 1;
	if (x < view.getTableSize() && y < view.getTableSize() && view.getFinish() == false) {
		if (model.getBoard()[x][y].getCheck() == ' ') {
			if (XO == 'O') {
				XO = 'X';
				view.gotoXY(m, n);
				model.setCurentTurn();
				model.getBoard()[x][y].setTurn(model.getCurentTurn());
				cout << XO;
				//cout << model.getCurentTurn();
			}
			else {
				XO = 'O';
				view.gotoXY(m, n);
				model.setCurentTurn();
				model.getBoard()[x][y].setTurn(model.getCurentTurn());
				cout << XO;
				//cout << model.getCurentTurn();
			}

		}model.getBoard()[x][y].setCheck(XO);
	}
}
void Controller::Player_1(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	system("cls");
	model.getBoard().clear();
	view.setFinish(false);
	model.getCurentTurn() = 0;

	/*int tableZise; cout << "Enter table size: "; cin >> tableZise;
	string table = to_string(tableZise);
	client.sendString(table);
	view.setTableSize(tableZise);
	view.showTableOnl();*/

	view.showTable();
	view.gotoXY(0, 2 * view.getTableSize() + 1);
	cout << p1->getName() << " turn: X" << "\t\t" << p2->getName() << " turn: O";
	model.setBoard(view.getTableSize());
	char XO = 'O';
	int x = 100;
	int y = 100;
	string recvX, recvY;
	while (true) {
		if (model.getCurentTurn() % 2 == 0) {
			COORD xy = view.checkClick();
			x = xy.X / 4; y = xy.Y / 2;
			//client.sendMsg(x, y);
			Click(x, y, XO); client.sendMsg(x, y);
			if (checkResult(x, y, XO) == 1) {
				if (XO == 'X') {
					view.gotoXY(0, 2 * view.getTableSize() + 3);
					cout << "CONGRATULATION player " << p1->getName();
					p1->setWinMatch(p1->getWinMatch() + 1);
					p2->setLoseMatch(p2->getLoseMatch() + 1);
					view.setFinish(true);
				}
				else {
					view.gotoXY(0, 2 * view.getTableSize() + 3);
					cout << "CONGRATULATION player " << p2->getName();
					p2->setWinMatch(p2->getWinMatch() + 1);
					p1->setLoseMatch(p1->getLoseMatch() + 1);
					view.setFinish(true);
				}
				break;
			}
		}
		else {
			if (client.recvMsg(x, y) == true) {
				Click(x, y, XO);
				if (checkResult(x, y, XO) == 1) {
					if (XO == 'X') {
						view.gotoXY(0, 2 * view.getTableSize() + 3);
						cout << "CONGRATULATION player " << p1->getName();
						p1->setWinMatch(p1->getWinMatch() + 1);
						p2->setLoseMatch(p2->getLoseMatch() + 1);
						view.setFinish(true);
					}
					else {
						view.gotoXY(0, 2 * view.getTableSize() + 3);
						cout << "CONGRATULATION player " << p2->getName();
						p2->setWinMatch(p2->getWinMatch() + 1);
						p1->setLoseMatch(p1->getLoseMatch() + 1);
						view.setFinish(true);
					}
					break;
				}
			}
		}
	}
	afterPlayer_1(p1, p2);
}
void Controller::Player_2(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	system("cls");
	model.getBoard().clear();
	model.getCurentTurn() = 0;
	view.setFinish(false);

	/*cout << "Waiting for player 1 setup " << endl;
	string table = client.recvString();
	int tableSize = atoi(table.c_str());
	view.setTableSize(tableSize);
	view.showTableOnl();*/

	view.showTable();
	view.gotoXY(0, 2 * view.getTableSize() + 1);
	cout << p1->getName() << " turn: X" << "\t\t" << p2->getName() << " turn: O";
	model.setBoard(view.getTableSize());
	char XO = 'O';
	int x = 100;
	int y = 100;
	string recvX, recvY;
	while (true) {
		if (model.getCurentTurn() % 2 == 0) {
			if (client.recvMsg(x, y) == true) {
				Click(x, y, XO);
				if (checkResult(x, y, XO) == 1) {
					if (XO == 'X') {
						view.gotoXY(0, 2 * view.getTableSize() + 3);
						cout << "CONGRATULATION player " << p1->getName();
						p1->setWinMatch(p1->getWinMatch() + 1);
						p2->setLoseMatch(p2->getLoseMatch() + 1);
						view.setFinish(true);
					}
					else {
						view.gotoXY(0, 2 * view.getTableSize() + 3);
						cout << "CONGRATULATION player " << p2->getName();
						p2->setWinMatch(p2->getWinMatch() + 1);
						p1->setLoseMatch(p1->getLoseMatch() + 1);
						view.setFinish(true);
					}
					break;
				}
			}

		}
		else {
			COORD xy = view.checkClick();
			x = xy.X / 4; y = xy.Y / 2;
			//client.sendMsg(x, y);
			Click(x, y, XO); client.sendMsg(x, y);
			if (checkResult(x, y, XO) == 1) {
				if (XO == 'X') {
					view.gotoXY(0, 2 * view.getTableSize() + 3);
					cout << "CONGRATULATION player " << p1->getName();
					p1->setWinMatch(p1->getWinMatch() + 1);
					p2->setLoseMatch(p2->getLoseMatch() + 1);
					view.setFinish(true);
				}
				else {
					view.gotoXY(0, 2 * view.getTableSize() + 3);
					cout << "CONGRATULATION player " << p2->getName();
					p2->setWinMatch(p2->getWinMatch() + 1);
					p1->setLoseMatch(p1->getLoseMatch() + 1);
					view.setFinish(true);
				}
				break;
			}
		}
	}
	afterPlayer_2(p1, p2);
}
void Controller::afterPlayer_1(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	while (true) {
		if (view.getFinish() == true) {

			view.gotoXY(50, 1);
			cout << "QUIT";
			view.gotoXY(50, 3);
			cout << "PLAY AGAIN";
			view.gotoXY(50, 5);
			cout << "REPLAY";
			view.gotoXY(50, 7);
			cout << "SAVE";

			COORD xy1 = view.checkClick();
			if ((xy1.X < 55 && xy1.X > 50) && (xy1.Y < 2 && xy1.Y > 0)) {
				system("cls");
				return;
				//this->run();
			}

			if ((xy1.X < 60 && xy1.X >50) && (xy1.Y < 4 && xy1.Y > 2)) {
				/*HANDLE       hStdOutput = NULL;
				view.cls(hStdOutput);*/
				Player_1(p1, p2);
				return;
			}

			if ((xy1.X < 57 && xy1.X > 50) && (xy1.Y < 6 && xy1.Y > 4)) {
				system("cls");
				this->ShowRePlay();
				return;
			}

			if ((xy1.X < 55 && xy1.X > 50) && (xy1.Y < 8 && xy1.Y > 6)) {
				system("cls");
				model.Gettemp().push_back(*p1);
				model.Gettemp().push_back(*p2);
				this->update(model.Gettemp());
				this->exportFile();
				return;
			}
		}
	}
}
void Controller::afterPlayer_2(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	while (true) {
		if (view.getFinish() == true) {

			view.gotoXY(50, 1);
			cout << "QUIT";
			view.gotoXY(50, 3);
			cout << "PLAY AGAIN";
			view.gotoXY(50, 5);
			cout << "REPLAY";
			view.gotoXY(50, 7);
			cout << "SAVE";

			COORD xy1 = view.checkClick();
			if ((xy1.X < 55 && xy1.X > 50) && (xy1.Y < 2 && xy1.Y > 0)) {
				system("cls");
				return;
				//this->run();
			}

			if ((xy1.X < 60 && xy1.X >50) && (xy1.Y < 4 && xy1.Y > 2)) {
				/*HANDLE       hStdOutput = NULL;
				view.cls(hStdOutput);*/
				Player_2(p1, p2);
				return;
			}

			if ((xy1.X < 57 && xy1.X > 50) && (xy1.Y < 6 && xy1.Y > 4)) {
				system("cls");
				this->ShowRePlay();
				return;
			}

			if ((xy1.X < 55 && xy1.X > 50) && (xy1.Y < 8 && xy1.Y > 6)) {
				system("cls");
				model.Gettemp().push_back(*p1);
				model.Gettemp().push_back(*p2);
				this->update(model.Gettemp());
				this->exportFile();
				return;
			}
		}
	}
}
void Controller::inToGame(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	system("cls");
	//client.createSocket();
	model.getBoard().clear();
	model.getCurentTurn() = 0;
	view.setFinish(false);
	view.showTable();
	view.gotoXY(0, 2 * view.getTableSize() + 1);
	cout << p1->getName() << " turn: X" << "\t\t" << p2->getName() << " turn: O";
	model.setBoard(view.getTableSize());
	char XO = 'O';
	while (true) {

		COORD xy = view.checkClick();

		Click(xy.X / 4, xy.Y / 2, XO);
		if (checkResult(xy.X / 4, xy.Y / 2, XO) == 1) {
			if (XO == 'X') {
				view.gotoXY(0, 2 * view.getTableSize() + 3);
				cout << "CONGRATULATION player " << p1->getName();
				p1->setWinMatch(p1->getWinMatch() + 1);
				p2->setLoseMatch(p2->getLoseMatch() + 1);
				view.setFinish(true);
			}
			else {
				view.gotoXY(0, 2 * view.getTableSize() + 3);
				cout << "CONGRATULATION player " << p2->getName();
				p2->setWinMatch(p2->getWinMatch() + 1);
				p1->setLoseMatch(p1->getLoseMatch() + 1);
				view.setFinish(true);
			}
		}
		if (checkResult(xy.X / 4, xy.Y / 2, XO) == 2) {
			view.gotoXY(0, 2 * view.getTableSize() + 3);
			cout << "Draw";
			view.setFinish(true);
		}
		view.gotoXY(50, 1);
		cout << "QUIT";
		if ((xy.X < 55 && xy.X > 50) && (xy.Y < 2 && xy.Y > 0)) {
			system("cls");
			return;
			//this->run();
		}
		if (view.getFinish() == true) {
			view.gotoXY(50, 3);
			cout << "PLAY AGAIN";
			if ((xy.X < 60 && xy.X >50) && (xy.Y < 4 && xy.Y > 2)) {
				/*HANDLE       hStdOutput = NULL;
				view.cls(hStdOutput);*/
				inToGame(p1, p2);
				return;
			}
		}
		if (view.getFinish() == true) {
			view.gotoXY(50, 5);
			cout << "REPLAY";
			if ((xy.X < 57 && xy.X > 50) && (xy.Y < 6 && xy.Y > 4)) {
				system("cls");
				this->ShowRePlay();
				return;
			}
		}
		if (view.getFinish() == true) {
			view.gotoXY(50, 7);
			cout << "SAVE";
			if ((xy.X < 55 && xy.X > 50) && (xy.Y < 8 && xy.Y > 6)) {
				system("cls");
				model.Gettemp().push_back(*p1);
				model.Gettemp().push_back(*p2);
				this->update(model.Gettemp());
				this->exportFile();
				return;
			}
		}
	}
}
void Controller::run() {
	//system("cls");
	model.Gettemp().clear();
	this->import();
	while (true) {
		view.Menu();
		int select;
		cout << "\nSelect: "; cin >> select;
		system("cls");
		switch (select)
		{
		case 1: {
			client.createSocket();
			shared_ptr<Player> p1(new Player);
			shared_ptr<Player> p2(new Player);
			string name1, name2;
			
			cout << "Enter your account: "; cin >> name1;
			if (account.login(name1) == 1) {
				cout << "Log in success!!!" << endl;
			}
			else {
				cout << "You don't have account! Let's create an account." << endl;
				system("pause");
				break;
			}
			p1->setName(name1);
			client.sendString(p1->getName());
			cout << "Waiting for player 2.... " << endl;
			//Reciver player 2 form client 2

			name2 = client.recvString();
			p2->setName(name2);
			cout << "Name of player 2: " << p2->getName() << endl;


			system("pause");
			Player_1(p1, p2);
			client.closeClient();
			break;
		}
		case 2: {
			client.createSocket();
			shared_ptr<Player> p1(new Player);
			shared_ptr<Player> p2(new Player);
			string name1, name2;

			cout << "Enter your account: "; cin >> name2;
			if (account.login(name2) == 1) {
				cout << "Log in success!!!" << endl;
			}
			else {
				cout << "You don't have account! Let's create an account." << endl;
				system("pause");
				break;
			}
			p2->setName(name2);
			client.sendString(p2->getName());
			cout << "Waiting for player 1.... " << endl;

			p1->setName(this->client.recvString());
			cout << "Name of player 1: " << p1->getName() << endl;

			system("pause");
			Player_2(p1, p2);
			client.closeClient();
			break;
		}
		case 3: {
			shared_ptr<Player> p1(new Player);
			shared_ptr<Player> p2(new Player);
			string name1, name2;

			cout << "Enter player1 name: "; cin >> name1;
			cout << "Enter player2 name: "; cin >> name2;

			p1->setName(name1); p2->setName(name2);

			inToGame(p1, p2);

			break;
		}
		case 4: {
			showData();
			system("pause");
			system("cls");
			break;
		}
		case 5: {
			account.createAccount();
			account.addAccIntoList();
			break;
		}
		case 6:
			account.showAccount();
			system("pause");
			system("cls");
			break;
		case 7:
			return;
		default:
			cout << "Please choose again." << endl;
			continue;
		}
	}
}
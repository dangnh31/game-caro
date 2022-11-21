#pragma once
#include "Client.h"
#include "View.h"
#include "Model.h"
#include "Account.h"

class Controller {
private:
	Client client;
	Model model;
	View view;
	Account account;
public:
	void run();
	void Click( int, int, char&);
	int checkResult(const int&, const int&, const unsigned char&);
	void inToGame(shared_ptr<Player> , shared_ptr<Player>);
	void ShowRePlay();
	void exportFile();
	void showData();
	void removeFile();
	void Player_1(shared_ptr<Player> , shared_ptr<Player> );
	void Player_2(shared_ptr<Player> , shared_ptr<Player> );
	void afterPlayer_1(shared_ptr<Player>, shared_ptr<Player>);
	void afterPlayer_2(shared_ptr<Player>, shared_ptr<Player>);
	void import();
	void update(vector<Player>&);
};
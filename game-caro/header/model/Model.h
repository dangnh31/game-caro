#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include"Point.h"
#include"Player.h"
#include<string>
using namespace std;
class Model {
private:
	vector<vector<Point> > Board;
	vector<Player> playerManager;
	vector < Player> temp;
	int currentTurn;
public:
	vector<vector<Point> >& getBoard();
	void setBoard(int );

	void setPlayerManager(vector<Player>);
	vector<Player>& getPlayerManager();

	void Settemp(vector<Player>);
	vector<Player>& Gettemp();
	
	void setCurentTurn();
	int &getCurentTurn();
};
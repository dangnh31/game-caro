#pragma once
#include<WS2tcpip.h>
#include<iostream>
#include<thread>
using namespace std;
#pragma comment (lib,"ws2_32.lib")
#define PORT 54000
class Server
{
public:
	Server();
	void setServer(SOCKET);
	SOCKET& getServer();

	void setFd_set(fd_set);
	fd_set& getFd_set();

	void setPortId(INT);
	INT getPortId();

	//static void setControl(Controller);
	//static Controller& getControl();


	void init_Server();
	static void handle(fd_set, SOCKET);
	void creat_thread();
	//void sendMsgtoClient(fd_set , string );
	//bool recvMsgfromClient(SOCKET , string& );
	~Server();

private:
	SOCKET listening;
	SOCKADDR_IN InternetAddr;
	INT nPortId;
	fd_set master;
};


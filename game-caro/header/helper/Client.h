#pragma once
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Client {
private:
	string ipAddress;			// IP Address of the server
	int port;
	SOCKET sock;
	//char buf[4096];
public:

	Client();
	// Create socket
	void createSocket();
	void sendMsg(int&, int&);
	bool recvMsg(int&, int&);
	void sendString(string);
	string recvString();
	void closeClient();

};


#include "Client.h"

Client::Client() {
	//this->ipAddress = "127.0.0.1";			// IP Address of the server
	//this->port = 54000;						// Listening port # on the server
	//WSAData data;
	//WORD ver = MAKEWORD(2, 2);
	//int wsResult = WSAStartup(ver, &data);
	//if (wsResult != 0)
	//{
	//	cerr << "Can't start Winsock, Err #" << wsResult << endl;
	//	return;
	//}
}
// Create socket
void Client::createSocket() {
	this->ipAddress = "127.0.0.1";			// IP Address of the server
	this->port = 54000;						// Listening port # on the server
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	else {
		// Fill in a hint structure
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		// Connect to server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
			closesocket(sock);
			WSACleanup();
			return;
		}
	}
}
void Client::sendMsg(int& x, int& y) {
	string buf = to_string(x) + " " + to_string(y);
	int sendResult{ 0 };

	sendResult = send(sock, buf.c_str(), buf.size() + 1, 0);
	if (sendResult > 0)
	{
		buf.clear();

	}
	return;
}
bool Client::recvMsg(int& x, int& y) {

	char buf[15];
	int bytesRecived;
	ZeroMemory(buf, 15);
	bytesRecived = recv(sock, buf, 15, 0);
	if (bytesRecived > 0)
	{
		char text[10];
		string s = string(buf, 0, 100);
		sscanf_s(s.c_str(), "%d %d %s", &x, &y, text, 10);
		return true;
	}
	return false;
}

void Client::sendString(string name) {
	send(sock, name.c_str(), name.size() + 1, 0);
}
string Client::recvString() {
	if (sock == INVALID_SOCKET)
	{
		return "Fail";
	}
	char buf[4096];
	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	return string(buf, 0, bytesReceived + 1);
}
void Client::closeClient() {
	closesocket(sock);
	WSACleanup();
}


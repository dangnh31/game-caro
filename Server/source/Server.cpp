#include "Client.h"
Server::Server() :nPortId(PORT) {}
void Server::setServer(SOCKET listening) { this->listening = listening; }
SOCKET& Server::getServer() { return this->listening; }
void Server::setFd_set(fd_set master) { this->master = master; }
fd_set& Server::getFd_set() { return master; }
void Server::setPortId(INT port) { this->nPortId = port; }
INT Server::getPortId() { return nPortId; }//void Server::setControl(Controller control1) { control = control1; }
//Controller& Server::getControl() { return control; }
//Server::control=NULL;


void Server::init_Server() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsData))
	{
		cerr << "Version isn't support !";
		return;
	}
	//creating socket
	this->listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't creat socket!" << endl;
		return;
	}
	//Bind the socket to an ip address and port
	// Khai báo cấu trúc địa chỉ
	//nPortId = 5105; // Khai báo cổng 
	InternetAddr.sin_family = AF_INET;// Họ địa chỉ Internet	
	InternetAddr.sin_addr.s_addr = INADDR_ANY; //sử dụng bất kì địa chỉ nào đều được !
	InternetAddr.sin_port = htons(nPortId);//Chuyển đổi cổng sang dạng network-byte order và gán cho trường sin_port
	bind(listening, (sockaddr*)&InternetAddr, sizeof(InternetAddr));
	//tell winsock the socket is for listeing 
	listen(listening, SOMAXCONN);
}
void Server::handle(fd_set master, SOCKET listening) {
	cout << "Create thread" << endl;
	string data;
	string check;
	while (true)
	{
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				/*string welcomeMsg = "Welcome to the Game Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
				for (int i = 0; i < master.fd_count; i++)
				{
					string msgInfo;
					if (i == 1) {
						msgInfo = "You are player 1 (X)\n";
					}
					if (i == 2) {
						msgInfo = "You are player 2 (O)\n";
					}
					SOCKET outSock = master.fd_array[i];
					send(outSock, msgInfo.c_str(), msgInfo.size() + 1, 0);
				}*/
				continue;
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);
				//accept a new message
				int byteIn = recv(sock, buf, 4096, 0);
				if (byteIn <= 0)
				{
					cout << "Error recive Msg form client #" << sock << ". Close program!" << endl;
					closesocket(sock);
					FD_CLR(sock, &master);
					return;
				}
				else
				{
					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							//ostringstream ss;
							//ss <</* "SOCKET #" << sock << ": " <<*/ buf << "\r\n";
							//string strOut = ss.str();
							cout << "SOCKET #" << sock << ": " << buf << "\n";
							/*send(outSock, strOut.c_str(), strOut.size()+1, 0);*/
							send(outSock, buf, 4096, 0);
						}

					}
				}
			}
		}
	}
}
void Server::creat_thread() {
	int countfd{ 0 };
	while (true)
	{
		int countSck{ 0 };
		fd_set master;
		FD_ZERO(&master);
		FD_SET(listening, &master);
		do
		{
	
			fd_set copy = master;
			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			for (int i = 0; i < socketCount; i++)
			{
				SOCKET sock = copy.fd_array[i];

				if (sock == listening) {
					//accept a new connection
					SOCKET client = accept(listening, nullptr, nullptr);
					//Add the new connection to the list of connection clients
					FD_SET(client, &master);
					//Send a welcome message to the connected client
					//string welcomeMsg = "Welcome to Server!";
					//send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
					countSck++;
					cout << "Add socket " << countSck << endl;
					//Broadcast we have a new connection
				}
			}
		} while (countSck < 2);
		
		

		thread th(handle, master, listening);
		th.detach();
		if (th.joinable()) {
			th.join();
		}

	}
}
Server::~Server() {
	closesocket(listening);
	//shutdow winsock
	WSACleanup();
}
void main()
{
	Server sckServer;
	sckServer.init_Server();
	sckServer.creat_thread();

}
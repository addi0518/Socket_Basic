#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class client
{
public:
	SOCKET clientSocket;
	SOCKADDR_IN serverAddr;
	int portNum;

	void portNumSet(int portNum);
	void socketSetting();
	void errorMessage(string message);
};
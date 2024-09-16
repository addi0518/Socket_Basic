#include "ClientHeader.h"

using namespace std;

void client::portNumSet(int portNum)
{
	this->portNum = portNum;
}

void client::socketSetting()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		errorMessage("INVALID_SOCKET");

	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); //���� ȯ�濡�� �׽�Ʈ �ϱ� ���� ������ �ּ�(127.0.0.1)
	serverAddr.sin_port = ::htons(portNum); //��Ʈ ��ȣ, 80 : HTTP

	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		errorMessage("SOCKET_ERROR");
}

void client::errorMessage(string message)
{
	cout << "Error : " << message << endl;
	system("pause"); // ���α׷� �Ͻ� ����
	exit(1); //���������� ��� ���μ��� ����
}

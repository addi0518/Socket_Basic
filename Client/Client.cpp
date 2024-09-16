#include <iostream>
#include "ClientHeader.h"

using namespace std;

constexpr int PORTNUM(7777);
constexpr int BUFFSIZE(100);

/*
* 1. ���� ����
* 2. ������ ���� ��û
* 3. ���
*/
int main()
{
    client c;

    WSADATA wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ���� API�� ����ϱ� ���� �ʱ�ȭ �۾�, Winsock 2.2 ������ ��û
        return 0;

    c.portNumSet(PORTNUM);

    c.socketSetting();

    //���� ���� ��
    cout << "Conneted To Server!" << endl;

    while (true)
    {

        char sendBuffer[BUFFSIZE];

        cout << "�޽��� : ";
        cin >> sendBuffer;

        int resultCode = ::send(c.clientSocket, sendBuffer, sizeof(sendBuffer), 0);
        if (resultCode == SOCKET_ERROR)
            return 0;

        char recvBuffer[BUFFSIZE];
        int recvLen = ::recv(c.clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (recvLen <= 0)
            return 0;

        cout << "Echo Data : " << recvBuffer << endl;
    }

    ::closesocket(c.clientSocket);
    ::WSACleanup();
}

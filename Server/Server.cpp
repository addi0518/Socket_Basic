#include <iostream>
#include "ServerHeader.h"

using namespace std;

constexpr int PORTNUM(7777);
constexpr int BUFFSIZE(100);

/*
*   1. ���ο� ���� ���� (socket)
*   2. ���Ͽ� �ּ�/��Ʈ ��ȣ ����(bind)
    3. ���Ͽ� �� ��Ű��(listen)
    4. �մ� ����(accept)
    5. Ŭ��� ���
*/
int main()
{
    WSADATA wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ���� API�� ����ϱ� ���� �ʱ�ȭ �۾�, Winsock 2.2 ������ ��û
        return 0;

    /*
    * 1�� ���� ����
    * ad : Address Family (AF_INET = IPv4, AF_INET6 = IPv6)
    * type : TCP(SOCK_STREAM) vs UPD(SOCK_DGRAM)
    * protocol : 0
    * return : descriptor
    * int32 errorCode = ::WSAGetLastError()
    */
    SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET)
        return 0;


    /*
    * 2. ���Ͽ� �ּ�/��Ʈ ��ȣ ����(bind)
    */
    SOCKADDR_IN serverAddr;
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); //IP �ּҸ� ���� (INADDR_ANY = IP �ּ� ��� ����)
    serverAddr.sin_port = ::htons(PORTNUM); //��Ʈ ��ȣ, 80 : HTTP

    if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        return 0;

    /*
    * 3. ���Ͽ� �� ��Ű��(listen)
    */
    if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    /*
    * 4. �մ� ����(accept)
    */
    while (true)
    {
        SOCKADDR_IN clientAddr;
        ::memset(&clientAddr, 0, sizeof(clientAddr));
        int addrLen = sizeof(clientAddr);


        SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen); //Ŭ���̾�Ʈ�� �ּ� �޾ƿ�
        if (clientSocket == INVALID_SOCKET)
            return 0;

        char ip[16];
        ::inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip)); //Ŭ���̾�Ʈ IP ����
        cout << "Client Conneted IP = " << ip << endl;

        while (true)
        {
            //��Ŷ
            char recvBuffer[BUFFSIZE];
            int recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
            if (recvLen <= 0)
                return 0;

            cout << "Receive Data : " << recvBuffer << endl;
            cout << "Receive Data Length : " << recvLen << endl;

            int resultCode = ::send(clientSocket, recvBuffer, recvLen, 0);
            if (resultCode == SOCKET_ERROR)
                return 0;
        }
    }

    ::closesocket(listenSocket);
    ::WSACleanup();
}


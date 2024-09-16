#include <iostream>
#include "ClientHeader.h"

using namespace std;

constexpr int PORTNUM(7777);
constexpr int BUFFSIZE(100);

/*
* 1. 소켓 생성
* 2. 서버에 연결 요청
* 3. 통신
*/
int main()
{
    client c;

    WSADATA wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // 소켓 API를 사용하기 위해 초기화 작업, Winsock 2.2 버전을 요청
        return 0;

    c.portNumSet(PORTNUM);

    c.socketSetting();

    //연결 성공 시
    cout << "Conneted To Server!" << endl;

    while (true)
    {

        char sendBuffer[BUFFSIZE];

        cout << "메시지 : ";
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

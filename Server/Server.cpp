#include <iostream>
#include "ServerHeader.h"

using namespace std;

constexpr int PORTNUM(7777);
constexpr int BUFFSIZE(100);

/*
*   1. 새로운 소켓 생성 (socket)
*   2. 소켓에 주소/포트 번호 설정(bind)
    3. 소켓에 일 시키기(listen)
    4. 손님 접속(accept)
    5. 클라와 통신
*/
int main()
{
    WSADATA wsaData;
    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // 소켓 API를 사용하기 위해 초기화 작업, Winsock 2.2 버전을 요청
        return 0;

    /*
    * 1번 소켓 생성
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
    * 2. 소켓에 주소/포트 번호 설정(bind)
    */
    SOCKADDR_IN serverAddr;
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); //IP 주소를 매핑 (INADDR_ANY = IP 주소 상관 없음)
    serverAddr.sin_port = ::htons(PORTNUM); //포트 번호, 80 : HTTP

    if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        return 0;

    /*
    * 3. 소켓에 일 시키기(listen)
    */
    if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    /*
    * 4. 손님 접속(accept)
    */
    while (true)
    {
        SOCKADDR_IN clientAddr;
        ::memset(&clientAddr, 0, sizeof(clientAddr));
        int addrLen = sizeof(clientAddr);


        SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen); //클라이언트의 주소 받아옴
        if (clientSocket == INVALID_SOCKET)
            return 0;

        char ip[16];
        ::inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip)); //클라이언트 IP 추출
        cout << "Client Conneted IP = " << ip << endl;

        while (true)
        {
            //패킷
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


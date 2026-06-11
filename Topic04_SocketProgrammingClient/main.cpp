#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;

	// Initialize Winsock
	(void)WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Create a socket
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Bind the socket
	SOCKADDR_IN socketAddr;
	ZeroMemory(&socketAddr, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &socketAddr.sin_addr);
	socketAddr.sin_port = htons(1234);

	connect(ClientSocket, (SOCKADDR*)&socketAddr, sizeof(socketAddr));

	char szRecvBuffer[1024];
	recv(ClientSocket, szRecvBuffer, sizeof(szRecvBuffer), 0);
	printf("%s", szRecvBuffer);

	const char* szSendBuffer = "The message is from client!!!";
	send(ClientSocket, szSendBuffer, strlen(szSendBuffer) + 1, 0);

	// Close client and server sockets
	closesocket(ClientSocket);

	// Stop using DLL
	WSACleanup();

	std::cin.get();
	return 0;
}
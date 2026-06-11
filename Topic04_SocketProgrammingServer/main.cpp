#include <winSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;

	// Initialize Winsock
	(void)WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Create a socket
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Bind the socket
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = htons(1234);
	bind(ListenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(ListenSocket, 20);

	// Create a client socket
	SOCKADDR clientAddr;
	int size = sizeof(clientAddr);
	SOCKET ClientSocket = accept(ListenSocket, &clientAddr, &size);

	const char* szSendBuffer = "The message is from server!!!";
	send(ClientSocket, szSendBuffer, strlen(szSendBuffer) + 1, 0);

	char szRecvBuffer[1024];
	recv(ClientSocket, szRecvBuffer, sizeof(szRecvBuffer), 0);
	printf("%s", szRecvBuffer);
	
	// Close client and server sockets
	closesocket(ClientSocket);
	closesocket(ListenSocket);

	// Stop using DLL
	WSACleanup();

	std::cin.get();
	return 0;
}
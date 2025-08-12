#include <winsock2.h>
#include <iostream>
#include <cstring>
#include "client.h"

#pragma comment(lib, "Ws2_32.lib")

bool Client::Connect() { 
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup error!" << std::endl;
        return false;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cout << "Socket Conn error!" << std::endl;
        WSACleanup();
        return false;
    }
    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1111);


    std::cout << "Conn to server..." << std::endl;
    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "" << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }
    std::cout << "Connected to server!" << std::endl;
    const char* message = "Hello from client!";

    if (send(sock, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cout << "Message failed!" << std::endl;
    } else {
        std::cout << "Message sent!" << std::endl;
    }

    char buffer[256];
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        std::cout << "Reply from server: " << buffer << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return true;
}

int main() {
    Client client;
    client.Connect();
    return 0;
}
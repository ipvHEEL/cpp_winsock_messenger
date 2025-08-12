#include <winsock2.h>
#include <iostream>
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
    bool RunServer() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "WSAStartup failed!" << std::endl;
            return false;
        }

        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cout << "Socket creation failed!" << std::endl;
            WSACleanup();
            return false;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
        serverAddr.sin_port = htons(1111); 

        if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cout << "Bind failed!" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cout << "Listen failed!" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        std::cout << "Server listening on port 1111..." << std::endl;

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Accept failed!" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        std::cout << "Client connected!" << std::endl;

        
        char buffer[256];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "mes: " << buffer << std::endl;
        } else {
            std::cout << "mes failed or connection closed." << std::endl;
        }

        
        const char* reply = "Message Message!";
        send(clientSocket, reply, strlen(reply), 0);


        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        std::cout << "Server shut down." << std::endl;
        return true;
    }
};

int main() {
    Server server;
    server.RunServer();
    
    return 0;
}
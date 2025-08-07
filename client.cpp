#include <winsock2.h>
#include <cstdio>
#include <ws2tcpip.h>  // Для inet_pton и т.д.
#define DEFAULT_PORT "27015"
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")


class Client{
public:
    bool start(){
        WSADATA wsaData;
        SOCKET ConnSocket = INVALID_SOCKET;
        struct addrinfo *result = nullptr, *ptr = nullptr, hints  = {};


         int resultWSA = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (resultWSA != 0){
            return false;
        }
        SOCKADDR_IN addr;
        int sizeofaddr = sizeof(addr);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(1111);
        addr.sin_family = AF_INET;
        
        SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
        
        if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) == SOCKET_ERROR){
            printf("Failed Client podkuchilsya");
        }
        else {
            printf("Vse norm");
        }

        char msg[256];
        recv(Connection, msg, sizeof(msg), 0);  
        system("Pause");
        
        
        
        return true;
    }
};



int main(){//TO DO: OOP
Client client;
client.start();
system("pause");
return 0;
}

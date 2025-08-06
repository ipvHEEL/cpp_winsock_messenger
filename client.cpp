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

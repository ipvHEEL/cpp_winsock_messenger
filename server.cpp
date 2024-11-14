#include <winsock2.h>
#include <cstdio>
#define DEFAULT_PORT "27015"
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

int main(){
WSADATA wsaData; 
int result;

WSAStartup(MAKEWORD(2,2), &wsaData);
SOCKADDR_IN addr;
int sizeofaddr = sizeof(addr);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
addr.sin_port = htons(1111);
addr.sin_family = AF_INET;

SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
listen(sListen, SOMAXCONN);


SOCKET newConnection;
newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
if(newConnection == 0 ){
    printf("Error of users's connect\n");
}
else{

printf("user's connection is already!\n");

char msg[256] = "Hellows, its my first server";
send(newConnection, msg, sizeof(msg), 0); 

}   
    system("pause");
    return 0;
}

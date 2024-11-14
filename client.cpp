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

SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);

if(connect(Connection, (SOCKADDR*)&addr, sizeofaddr)){
    printf("Error of client's socket connection\n");
}

printf("Client's socket already connect!!ura\n");

char msg[256];
recv(Connection, msg, sizeof(msg), 0);
for(int i = 0;i<sizeof(msg) - 1; i++){
    printf("%c", msg[i]);
}
system("pause");
return 0;
}

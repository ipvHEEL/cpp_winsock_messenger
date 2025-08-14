#ifdef CLIENT_H
#define CLIENT_H

#include <winsock.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

class Client {
public:
    bool Connect();
};

#endif
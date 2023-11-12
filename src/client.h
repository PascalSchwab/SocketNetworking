#ifndef CLIENT_H
#define CLIENT_H

#include "main.h"

typedef struct{
    int socketfd;
    struct sockaddr_in *p_address;
} Client;

Client* CreateClient(char *p_ipAddress, int port, SocketType type, ProtocolFamily family);

void ConnectClient(Client *p_client);

void DisposeClient(Client *p_client);

#endif
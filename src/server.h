#ifndef SERVER_H
#define SERVER_H

#include "main.h"

#define MAX_CLIENTS 10

typedef struct{
    int socketfd;
    struct sockaddr_in *p_address;
    int clientSocket;
} Server;

Server* CreateServer(int port, SocketType type, ProtocolFamily family);

void BindServerSocket(Server *p_server);

void SetServerOptions(Server *p_server);

void ListenServer(Server *p_server);

void DisposeServer(Server *p_server);

#endif
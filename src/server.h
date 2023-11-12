#ifndef SERVER_H
#define SERVER_H

#include "main.h"

#define MAX_CLIENTS 10

typedef struct{
    int socketfd;
    struct sockaddr_in *p_address;
} Server;

typedef struct{
    Server *p_server;
    int socketfd;
    void (*callbackFunc)(char*);
}ServerClient;

Server* CreateServer(int port, SocketType type, ProtocolFamily family);

void BindServerSocket(Server *p_server);

void SetServerOptions(Server *p_server);

void ListenServer(Server *p_server, void (*callbackFunc)(char*));

void* HandleClient(void *p);

void DisposeServer(Server *p_server);

#endif
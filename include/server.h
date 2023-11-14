#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 10

#include "socket.h"

typedef struct{
    Socket *p_server;
    int socketfd;
    void (*callbackFunc)(char*);
}ServerClient;

Socket* CreateServer(int port, SocketType type, ProtocolFamily family);

void BindServerSocket(Socket *p_server);

void SetServerOptions(Socket *p_server);

void ListenServer(Socket *p_server, void (*callbackFunc)(char*));

static void* HandleClient(void *p);

void DisposeServer(Socket *p_server);

#endif
#ifndef SOCKET_H
#define SOCKET_H

#include "main.h"

#define RECIEVE_BUFFER_SIZE 1024

int CreateSocket(ProtocolFamily family, SocketType type);

struct sockaddr_in* CreateAddress(ProtocolFamily family, char *p_ipAddress, int port);

void DisposeSocket(Socket *p_socket);

void SendStringMessage(Socket *p_socket, char *p_message);

int PackInt(int number);

#endif
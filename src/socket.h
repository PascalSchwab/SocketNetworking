#ifndef SOCKET_H
#define SOCKET_H

#include "main.h"

int CreateSocket(ProtocolFamily family, SocketType type);

struct sockaddr_in* CreateAddress(ProtocolFamily family, char *p_ipAddress, int port);

void DisposeSocket(int socketfd, struct sockaddr_in *p_address);

int PackInt(int number);

#endif
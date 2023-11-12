#ifndef CLIENT_H
#define CLIENT_H

#include "main.h"

Socket* CreateClient(char *p_ipAddress, int port, SocketType type, ProtocolFamily family);

void ConnectClient(Socket *p_client);

void DisposeClient(Socket *p_client);

#endif
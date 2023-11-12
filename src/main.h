#ifndef MAIN_H
#define MAIN_H

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef enum{
    TCP = SOCK_STREAM, UDP = SOCK_DGRAM
} SocketType;

typedef enum{
    IPV4 = AF_INET, IPV6 = AF_INET6, BLUETOOTH = AF_BLUETOOTH
} ProtocolFamily;

typedef struct{
    int socketfd;
    struct sockaddr_in *p_address;
} Socket;

#define ERROR 1
#define SUCCESS 0

#include "socket.h"
#include "client.h"
#include "server.h"

#endif
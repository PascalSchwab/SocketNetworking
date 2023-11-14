#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "client.h"
#include "lib.h"

Socket* CreateClient(char *p_ipAddress, int port, SocketType type, ProtocolFamily family){
    Socket *p_client = malloc(sizeof(Socket));
    p_client->socketfd = CreateSocket(family, type);
    p_client->p_address = CreateAddress(family, p_ipAddress, port);
    printf("Client was created\n");
    return p_client;
}

void ConnectClient(Socket *p_client){
    if(connect(p_client->socketfd, (struct sockaddr *)p_client->p_address, sizeof(*(p_client->p_address))) < 0){
        perror("Failed to connect to server");
        DisposeClient(p_client);
        exit(ERROR);
    }
    printf("Client connected to the server\n");
}

void DisposeClient(Socket *p_client){
    DisposeSocket(p_client);
    printf("Client was deleted\n");
}
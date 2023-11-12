#include "client.h"

Client* CreateClient(char *p_ipAddress, int port, SocketType type, ProtocolFamily family){
    Client *p_client = malloc(sizeof(Client));
    p_client->socketfd = CreateSocket(family, type);
    p_client->p_address = CreateAddress(family, p_ipAddress, port);
    printf("Client was created\n");
    return p_client;
}

void ConnectClient(Client *p_client){
    if(connect(p_client->socketfd, (struct sockaddr *)p_client->p_address, sizeof(*(p_client->p_address))) < 0){
        perror("Failed to connect to server");
        DisposeClient(p_client);
        exit(ERROR);
    }
    printf("Client connected to the server\n");
}

void DisposeClient(Client *p_client){
    DisposeSocket(p_client->socketfd, p_client->p_address);
    free(p_client);
    printf("Client was deleted\n");
}
#include "socket.h"

int CreateSocket(ProtocolFamily family, SocketType type){
    int socketfd = socket(family, type, 0);
    if(socketfd < 0){
        perror("Error by creating socket\n");
        exit(ERROR);
    }
    return socketfd;
}

struct sockaddr_in* CreateAddress(ProtocolFamily family, char *p_ipAddress, int port){
    struct sockaddr_in *p_address = malloc(sizeof(struct sockaddr_in));
    p_address->sin_port = PackInt(port);
    p_address->sin_family = family;

    if(p_ipAddress == NULL){
        p_address->sin_addr.s_addr = INADDR_ANY;
    }
    else{
        if(inet_pton(family, p_ipAddress, &p_address->sin_addr) < 0){
            perror("Invalid address\n");
            free(p_address);
            exit(ERROR);
        }
    }
    return p_address;
}

void DisposeSocket(int socketfd, struct sockaddr_in *p_address){
    close(socketfd);
    free(p_address);
}

int PackInt(int number){
    return htons(number);
}
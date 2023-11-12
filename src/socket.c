#include "socket.h"

int CreateSocket(ProtocolFamily family, SocketType type){
    int socketfd = socket(family, type, 0);
    if(socketfd < 0){
        perror("Error by creating socket");
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
            perror("Invalid address");
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

int SendStringMessage(int socketfd, char *p_message){
    return send(socketfd, p_message, strlen(p_message), 0);
}

int PackInt(int number){
    return htons(number);
}
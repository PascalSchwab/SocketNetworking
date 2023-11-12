#include "server.h"

Server* CreateServer(int port, SocketType type, ProtocolFamily family){
    Server *p_server = malloc(sizeof(Server));
    p_server->socketfd = CreateSocket(family, type);
    p_server->p_address = CreateAddress(family, NULL, port);
    printf("Server was created\n");
    return p_server;
}

void SetServerOptions(Server *p_server){
    int opt = 1;
    if(setsockopt(p_server->socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("Can't set socket opt");
        DisposeServer(p_server);
        exit(ERROR);
    }
}

void BindServerSocket(Server *p_server){
    if(bind(p_server->socketfd, (struct sockaddr*)p_server->p_address, sizeof(*p_server->p_address)) < 0){
        perror("Bind socket to port failed");
        DisposeServer(p_server);
        exit(ERROR);
    }
}

void ListenServer(Server *p_server){
    // Listen
    if(listen(p_server->socketfd, MAX_CLIENTS) < 0){
        perror("Set socket into listen mode failed");
        DisposeServer(p_server);
        exit(ERROR);
    }

    printf("Server is listenting. Waiting for connections...\n");

    // Accept one incoming client
    struct sockaddr_in connectionAddress;
    int lengthOfAddress = sizeof(connectionAddress);
    p_server->clientSocket = accept(p_server->socketfd, (struct sockaddr*)&connectionAddress, &lengthOfAddress);

    if(p_server->clientSocket < 0){
        perror("Can't accept incoming connection");
        DisposeServer(p_server);
        exit(ERROR);
    }
}

void DisposeServer(Server *p_server){
    DisposeSocket(p_server->socketfd, p_server->p_address);
    free(p_server);
    close(p_server->clientSocket);
    printf("Server was deleted\n");
}
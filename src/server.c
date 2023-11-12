#include "server.h"

Socket* CreateServer(int port, SocketType type, ProtocolFamily family){
    Socket *p_server = malloc(sizeof(Socket));
    p_server->socketfd = CreateSocket(family, type);
    p_server->p_address = CreateAddress(family, NULL, port);
    printf("Server was created\n");
    return p_server;
}

void SetServerOptions(Socket *p_server){
    int opt = 1;
    if(setsockopt(p_server->socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("Can't set socket opt");
        DisposeServer(p_server);
        exit(ERROR);
    }
}

void BindServerSocket(Socket *p_server){
    if(bind(p_server->socketfd, (struct sockaddr*)p_server->p_address, sizeof(*p_server->p_address)) < 0){
        perror("Bind socket to port failed");
        DisposeServer(p_server);
        exit(ERROR);
    }
}

void ListenServer(Socket *p_server, void (*callbackFunc)(char*)){
    // Listen
    if(listen(p_server->socketfd, MAX_CLIENTS) < 0){
        perror("Set socket into listen mode failed");
        DisposeServer(p_server);
        exit(ERROR);
    }

    printf("Server is listenting. Waiting for connections...\n");

    while(1){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        int socketfd = accept(p_server->socketfd, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if(socketfd < 0){
            perror("Can't accept incoming connection");
            DisposeServer(p_server);
            exit(ERROR);
        }

        ServerClient *p_client = malloc(sizeof(ServerClient));
        p_client->socketfd = socketfd;
        p_client->callbackFunc = callbackFunc;
        p_client->p_server;

        pthread_t id;
        pthread_create(&id, NULL, HandleClient, p_client);
        pthread_join(id, NULL);
    }
}

void* HandleClient(void *p){
    ServerClient *p_client = (ServerClient*)p;
    char message[RECIEVE_BUFFER_SIZE];
    if(recv(p_client->socketfd, message, RECIEVE_BUFFER_SIZE, 0) < 0){
        perror("Can't read message\n");
        DisposeServer(p_client->p_server);
        exit(ERROR);
    }
    p_client->callbackFunc(message);
    free(p_client);
}

void DisposeServer(Socket *p_server){
    DisposeSocket(p_server);
    printf("Server was deleted\n");
}
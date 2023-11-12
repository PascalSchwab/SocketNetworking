#include "main.h"

int main(){
    // Server
    Server *p_server = CreateServer(5005, TCP, IPV4);
    SetServerOptions(p_server);
    BindServerSocket(p_server);
    ListenServer(p_server);
    RecvStringMessage *p_result = RecieveStringMessage(p_server->clientSocket);
    if(p_result->exitCode < 0){
        perror("Can't read message\n");
        DisposeServer(p_server);
        exit(ERROR);
    }
    printf("%s\n", p_result->message);
    DisposeServer(p_server);

    // Client
    // Client *p_client = CreateClient("127.0.0.1", 5005, TCP, IPV4);
    // ConnectClient(p_client);
    // SendStringMessage(p_client->socketfd, "Hello World");
    // DisposeClient(p_client);
    return SUCCESS;
}
#include "main.h"

#define PORT 5005

void printMessage(char* message){
    printf("%s\n", message);
}

void StartServer(){
    Socket *p_server = CreateServer(PORT, TCP, IPV4);
    SetServerOptions(p_server);
    BindServerSocket(p_server);
    ListenServer(p_server, printMessage);
    DisposeServer(p_server);
}

void StartClient(){
    Socket *p_client = CreateClient("127.0.0.1", PORT, TCP, IPV4);
    ConnectClient(p_client);
    SendStringMessage(p_client, "Hello World");
    DisposeClient(p_client);
}

int main(){
    // Server
    StartServer();

    // Client
    // StartClient();
    return SUCCESS;
}
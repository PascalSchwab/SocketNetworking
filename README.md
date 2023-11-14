# SocketNetworking
Library for Socket Programming in C

# Server
    #include "network.h"
    #include <stdio.h>

    void printMessage(char* message){
        printf("%s\n", message);
    }

    int main(){
        Socket *p_server = CreateServer(5001, TCP, IPV4);

        SetServerOptions(p_server);

        BindServerSocket(p_server);

        ListenServer(p_server, printMessage);

        DisposeServer(p_server);

        return 0;
    }

# Client
    #include "network.h"

    int main(){
        Socket *p_client = CreateClient("127.0.0.1", 5001, TCP, IPV4);

        ConnectClient(p_client);

        SendStringMessage(p_client, "Hello World");
        
        DisposeClient(p_client);

        return 0;
    }

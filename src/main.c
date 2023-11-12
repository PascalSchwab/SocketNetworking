#include "main.h"

int main(){
    // Server
    // Server *p_server = CreateServer(5005, TCP, IPV4);
    // SetServerOptions(p_server);
    // BindServerSocket(p_server);
    // ListenServer(p_server);
    // DisposeServer(p_server);

    // Client
    Client *p_client = CreateClient("127.0.0.1", 5005, TCP, IPV4);
    Connect(p_client);
    DisposeClient(p_client);
    return SUCCESS;
}
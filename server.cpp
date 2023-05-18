#include "server.h"

/**
 * Constructor
 * @param int Port
 * @param void*()(RecievedMessage*) Callback function
 * @param SocketType TCP or UDP (Default: TCP)
 * @param ProtocolFamily IPv4, IPv6 or Bluetooth (Default: IPv4)
 * @param int Count, how much clients are allowed to wait in the acception queue (Default: 3)
*/
Server::Server(int port, void (*callbackFunc)(struct RecievedMessage* recievedMessage), SocketType socketType, ProtocolFamily family, int queueClientSize) : Socket(port, socketType, family){
    this->callbackFunc = callbackFunc;
    this->m_QueueCLientSize = queueClientSize;
}

/**
 * Starts the server (Create socket, Bind address, Listen on socket, Accept connections)
 * @return int (0 = Created; 1 = Failed)
*/
int Server::Start(){
    // Create socket
    if(CreateSocket() == 1){
        return 1;
    }

    // Create address
    if(CreateAddress() == 1){
        return 1;
    }

    // Bind socket
    if(bind(this->m_Socket, (struct sockaddr*)this->m_Address, sizeof(*(this->m_Address))) == -1){
        cerr << "Binding socket to address failed" << endl;
        close(this->m_Socket);
        return 1;
    }

    cout << "Server was created" << endl;

    // Set socket into listen mode
    if(listen(this->m_Socket, this->m_QueueCLientSize) == -1){
        cerr << "Listen on socket failed" << endl;
        close(this->m_Socket);
        return 1;
    }

    cout << "Server is listening on port: " << this->m_Port << ". Waiting for connections ..." << endl;

    // Accept Connections
    AcceptConnections();

    return 0;
}

/**
 * Accept incoming connections and opens for each client a thread
*/
void Server::AcceptConnections(){
    while(true){
        // Add incoming client to client list
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        int clientSocket = accept(this->m_Socket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if(clientSocket == -1){
            cerr << "Can't accept incoming client connection" << endl;
            break;
        }

        // Create Server client
        struct ServerClient* serverClient = (struct ServerClient*) malloc(sizeof(struct ServerClient));
        serverClient->socket = clientSocket;
        char* clientIp = inet_ntoa(clientAddress.sin_addr);
        serverClient->address = clientIp;

        this->m_ServerClients.push_back(serverClient);

        // Open new thread for client
        thread t(HandleClient, ref(serverClient), ref(this->m_ServerClients), this->callbackFunc);
        t.detach();
    }
}

/**
 * Handles new client in own thread (Recieve messages and call callback function)
 * @param ServerClient* Client socket
 * @param vector<ServerClient*> client list
 * @param void*()(RecievedMessage*) Callback function
*/
void Server::HandleClient(struct ServerClient* &client, vector<struct ServerClient*> &serverClients, void(*callbackFunc)(struct RecievedMessage* recievedMessage)){
    char message[1024] = {0};
    
    // Recieve message from client
    int recieve = recv(client->socket, message, 1024, 0);
    if(recieve == -1){
        cerr << "Failed to revcieve message from client" << endl;
    }
    else{
        // Call callback function
        struct RecievedMessage* recievedMessage = (struct RecievedMessage*)malloc(sizeof(struct RecievedMessage));
        recievedMessage->client = client;
        recievedMessage->message = message;
        callbackFunc(recievedMessage);
        memset(message, 0, sizeof(message));
        free(recievedMessage);
    }

    // Remove Client Socket
    auto it = find(serverClients.begin(), serverClients.end(), client);
    if(it != serverClients.end()){
        serverClients.erase(it);
    }

    close(client->socket);
    free(client);
}

Server::~Server(){
    cout << "Server was shut down" << endl;
}
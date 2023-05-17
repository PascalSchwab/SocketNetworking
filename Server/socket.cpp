#include "socket.h"

Socket::Socket(int port, SocketType socketType, ProtocolFamily family){
    // Init members
    this->m_Port = port;
    this->m_SocketType = socketType;
    this->m_ProtocolFamily = family;
}

int Socket::Listen(void (*callbackFunc)(string message), int queueClientSize){
    // Create socket
    if(CreateSocket() == 1){
        return 1;
    }

    printf("Socket was created\n");

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

    // Set socket into listen mode
    if(listen(this->m_Socket, queueClientSize) == -1){
        cerr << "Listen on socket failed" << endl;
        close(this->m_Socket);
        return 1;
    }

    printf("Socket listen on port %d. Waiting for connections ...\n", this->m_Port);

    // Accept Connections
    AcceptConnections(callbackFunc);

    return 0;
}

int Socket::Connect(){
    // Create socket
    if(CreateSocket() == 1){
        return 1;
    }

    printf("Socket was created\n");

    // Create address
    if(CreateAddress("127.0.0.1") == 1){
        return 1;
    }

    // Connect
    if(connect(this->m_Socket, (struct sockaddr *)this->m_Address, sizeof(*(this->m_Address))) == -1){
        cerr << "Failed to connect to server" << endl;
        return 1;
    }

    // Thread for receiving messages (Future)

    return 0;
}

int Socket::SendMessage(string message){
    if(send(this->m_Socket, message.c_str(), message.length(), 0) == -1){
        cerr << "Failed to send message to the server" << endl;
        return 1;
    }
    return 0;
}

void Socket::HandleCLient(int clientSocket, vector<int> &clientSockets, void (*callbackFunc)(string message)){
    char message[1024] = {0};

    // while(true){
    //     // Recieve message from client
    //     int recieve = recv(clientSocket, message, 1024, 0);
    //     if(recieve == -1){
    //         cerr << "Failed to revcieve message from client" << endl;
    //         break;
    //     }
    //     callbackFunc(message);
    //     memset(message, 0, sizeof(message));
    // }
    
    // Recieve message from client
    int recieve = recv(clientSocket, message, 1024, 0);
    if(recieve == -1){
        cerr << "Failed to revcieve message from client" << endl;
    }
    else{
        callbackFunc(message);
        memset(message, 0, sizeof(message));
    }

    // Remove Client Socket
    auto it = find(clientSockets.begin(), clientSockets.end(), clientSocket);
    if(it != clientSockets.end()){
        clientSockets.erase(it);
    }
    close(clientSocket);
}

void Socket::AcceptConnections(void (*callbackFunc)(string message)){
    // Accept incoming connections
    vector<int> clientSockets;

    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        int clientSocket = accept(this->m_Socket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if(clientSocket == -1){
            cerr << "Can't accept incoming client connection" << endl;
            break;
        }
        clientSockets.push_back(clientSocket);

        thread t(HandleCLient, clientSocket, ref(clientSockets), callbackFunc);
        t.detach();
    }
}

int Socket::CreateSocket(){
    this->m_Socket = socket(this->m_ProtocolFamily, this->m_SocketType, 0);

    if(m_Socket == -1){
        cerr << "Socket creation failed" << endl;
        return 1;
    }
    return 0;
}

int Socket::CreateAddress(const char* ipAddress){
    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    address->sin_port = htons(this->m_Port);
    address->sin_family = this->m_ProtocolFamily;

    if(ipAddress == NULL){
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else{
        if(inet_pton(this->m_ProtocolFamily, ipAddress, &address->sin_addr) <= 0){
            cerr << "Invalid address. Address creation failed" << endl;
            return 1;
        }
    }

    this->m_Address = address;
    return 0;
}

Socket::~Socket(){
    close(this->m_Socket);
    printf("Socket was deleted\n");
}
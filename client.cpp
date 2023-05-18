#include "client.h"

Client::Client(int port, string serverAddress, SocketType socketType, ProtocolFamily family) : Socket(port, socketType, family){
    this->m_ServerAddress = serverAddress;
}

int Client::Connect(){
    // Create socket
    if(CreateSocket() == 1){
        return 1;
    }

    // Create address
    if(CreateAddress(this->m_ServerAddress.c_str()) == 1){
        return 1;
    }

    cout << "Client was created" << endl;

    // Connect
    if(connect(this->m_Socket, (struct sockaddr *)this->m_Address, sizeof(*(this->m_Address))) == -1){
        cerr << "Failed to connect to server" << endl;
        return 1;
    }

    cout << "Client is connected to server: " << this->m_ServerAddress << endl;

    // Thread for receiving messages (Future)

    return 0;
}

int Client::SendMessage(string message){
    int send = Socket::SendMessage(this->m_Socket, message);
    if(send != 1){
        cout << "Client has send message: \"" << message << "\" to the server" << endl;
    }
    return send;
}

Client::~Client(){
    cout << "Client was shut down" << endl;
}
#include "socket.h"

Socket::Socket(int port, SocketType socketType, ProtocolFamily family){
    // Init members
    this->m_Port = port;
    this->m_SocketType = socketType;
    this->m_ProtocolFamily = family;
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

int Socket::SendMessage(int socket, string message){
    if(send(socket, message.c_str(), message.length(), 0) == -1){
        cerr << "Failed to send message" << endl;
        return 1;
    }
    return 0;
}

Socket::~Socket(){
    close(this->m_Socket);
}
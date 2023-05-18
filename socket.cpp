#include "socket.h"

/**
 * Socket Constructor
 * @param int Port
 * @param SocketType TCP or UDP (Default: TCP)
 * @param ProtocolFamily IPv4, IPv6 or Bluetooth (Default: IPv4)
*/
Socket::Socket(int port, SocketType socketType, ProtocolFamily family){
    this->m_Port = port;
    this->m_SocketType = socketType;
    this->m_ProtocolFamily = family;
}

/**
 * Creates a new socket
 * @return int (0 = Created; 1 = Failed)
*/
int Socket::CreateSocket(){
    this->m_Socket = socket(this->m_ProtocolFamily, this->m_SocketType, 0);
    // Check for failure
    if(m_Socket == -1){
        cerr << "Socket creation failed" << endl;
        return 1;
    }
    return 0;
}

/**
 * Creates a new address, which you can bind with a socket
 * @param std::string IP-Address of the Server (Default: NULL)
 * @return int (0 = Created; 1 = Failed)
*/
int Socket::CreateAddress(string ipAddress){
    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    address->sin_port = htons(this->m_Port);
    address->sin_family = this->m_ProtocolFamily;

    // IP-Address is empty -> Server
    if(ipAddress.empty()){
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else{
        // IP-Address not empty -> Client and convert to IPv6
        if(inet_pton(this->m_ProtocolFamily, ipAddress.c_str(), &address->sin_addr) <= 0){
            cerr << "Invalid address. Address creation failed" << endl;
            return 1;
        }
    }

    this->m_Address = address;
    return 0;
}

/**
 * Sends message to specific socket
 * @param int Target Socket
 * @param std::string Message, which should be sended
 * @return int (0 = Created; 1 = Failed)
*/
int Socket::SendMessage(int socket, string message){
    if(send(socket, message.c_str(), message.length(), 0) == -1){
        cerr << "Failed to send message" << endl;
        return 1;
    }
    return 0;
}

// Close Socket, when deconstructed
Socket::~Socket(){
    close(this->m_Socket);
}
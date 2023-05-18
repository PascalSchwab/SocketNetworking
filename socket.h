#ifndef __SOCKET__
#define __SOCKET__

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

enum SocketType{
    TCP = SOCK_STREAM, UDP = SOCK_DGRAM
};

enum ProtocolFamily{
    IPV4 = AF_INET, IPV6 = AF_INET6, BLUETOOTH = AF_BLUETOOTH
};

/*
    Socket is like a door to communicate between hosts. It can be a server or a client.
    It has a port, an address, a transportation protocol and a data link protocol.
*/
class Socket{
    public:
        Socket(int port, SocketType socketType, ProtocolFamily family);
        ~Socket();
        // @return int - Socket Port
        int GetPort() const {return m_Port;}
        // @return SocketType - TCP or UDP
        SocketType GetSocketType() const {return m_SocketType;}
        // @return ProtocolFamily - IPv4, IPv6 or Bluetooth
        ProtocolFamily GetProtocolFamily() const {return m_ProtocolFamily;}
        int SendMessage(int socket, string message);
    protected:
        int CreateSocket();
        int CreateAddress(const char* ipAdress = NULL);
    protected:
        int m_Socket;
        int m_Port;
        SocketType m_SocketType;
        ProtocolFamily m_ProtocolFamily;
        const struct sockaddr_in* m_Address;
};

#endif
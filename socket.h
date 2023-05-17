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

class Socket{
    public:
        Socket(int port, SocketType socketType = TCP, ProtocolFamily family = IPV4);
        ~Socket();
        int Listen(void (*callbackFunc)(string message), int queueClientSize = 3);
        int Connect();
        int SendMessage(string message);
        int GetSocket() const { return m_Socket; }
        int GetPort() const {return m_Port;}
        SocketType GetSocketType() const {return m_SocketType;}
        ProtocolFamily GetProtocolFamily() const {return m_ProtocolFamily;}
        const struct sockaddr_in* GetAddress() const { return m_Address; } 
    private:
        int CreateSocket();
        int CreateAddress(const char* ipAddress = NULL);
        void AcceptConnections(void (*callbackFunc)(string message));
        static void HandleCLient(int clientSocket, vector<int> &clientSockets, void (*callbackFunc)(string message));
    private:
        int m_Socket;
        int m_Port;
        SocketType m_SocketType;
        ProtocolFamily m_ProtocolFamily;
        const struct sockaddr_in* m_Address;
};

#endif
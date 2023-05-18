#ifndef __CLIENT__
#define __CLIENT__

#include "socket.h"

class Client : Socket{
    public:
        Client(int port, string serverAddress, SocketType socketType = TCP, ProtocolFamily family = IPV4);
        ~Client();
        int Connect();
        string GetServerAddress() const {return m_ServerAddress;}
        int SendMessage(string message);
    private:
        string m_ServerAddress;
};

#endif
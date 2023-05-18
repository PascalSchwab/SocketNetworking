#ifndef __CLIENT__
#define __CLIENT__

#include "socket.h"

/*
    Client, which can connect to any server and send messages to it
*/
class Client : Socket{
    public:
        Client(int port, string serverAddress, SocketType socketType = TCP, ProtocolFamily family = IPV4);
        ~Client();
        int Connect();
        // @return std::string - Server address
        string GetServerAddress() const {return m_ServerAddress;}
        int SendMessage(string message);
    private:
        string m_ServerAddress;
};

#endif
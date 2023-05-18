#ifndef __SERVER__
#define __SERVER__

#include "socket.h"

/*
    Server, which listens on a specific port and clients can send messages to it.
    Server decides with a callback function what should be done with a message 
*/
class Server : Socket{
    public:
        // Callback Function, when message arrived @param std::string Arrived message
        void (*callbackFunc)(string message);
    public:
        Server(int port, void (*callbackFunc)(string message), SocketType socketType = TCP, ProtocolFamily family = IPV4, int queueClientSize = 3);
        ~Server();
        int Start();
    private:
        void AcceptConnections();
        static void HandleCLient(int clientSocket, vector<int> &clientSockets, void (*callbackFunc)(string message));
    private:
        int m_QueueCLientSize;
        vector<int> m_ClientSockets;
};

#endif
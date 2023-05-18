#ifndef __SERVER__
#define __SERVER__

#include "socket.h"

class Server : Socket{
    public:
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
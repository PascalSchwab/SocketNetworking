#ifndef __SERVER__
#define __SERVER__

#include "socket.h"

/*
    Client in the server has a socket id and an address
*/
struct ServerClient{
    int socket;
    string address;
};

/*
    Recieved message has the client, which has sended the message, and the message itself
*/
struct RecievedMessage{
    struct ServerClient* client;
    string message;
};

/*
    Server, which listens on a specific port and clients can send messages to it.
    Server decides with a callback function what should be done with a message 
*/
class Server : Socket{
    public:
        // Callback Function, when message arrived @param RecievedMessage* Recieved message
        void (*callbackFunc)(struct RecievedMessage* message);
    public:
        Server(int port, void (*callbackFunc)(struct RecievedMessage* message), SocketType socketType = TCP, ProtocolFamily family = IPV4, int queueClientSize = 3);
        ~Server();
        int Start();
        static void call(struct RecievedMessage* message);
    private:
        void AcceptConnections();
        static void HandleClient(struct ServerClient* &client, vector<struct ServerClient*> &serverClients, void(*callbackFunc)(struct RecievedMessage* message));
    private:
        int m_QueueCLientSize;
        vector<struct ServerClient*> m_ServerClients;
};

#endif
typedef enum{
    TCP = SOCK_STREAM, UDP = SOCK_DGRAM
} SocketType;

typedef enum{
    IPV4 = AF_INET, IPV6 = AF_INET6, BLUETOOTH = AF_BLUETOOTH
} ProtocolFamily;

typedef struct{
    int socketfd;
    struct sockaddr_in *p_address;
} Socket;

#define RECIEVE_BUFFER_SIZE 1024

int CreateSocket(ProtocolFamily family, SocketType type);

struct sockaddr_in* CreateAddress(ProtocolFamily family, char *p_ipAddress, int port);

void DisposeSocket(Socket *p_socket);

void SendStringMessage(Socket *p_socket, char *p_message);

int PackInt(int number);
# SocketNetworking

# Server
#include "socket.h"

void callback(string message){
    std::cout << message << std::endl;
}

int main(){
    Socket socket(8080);

    // Server
    if(socket.Listen(callback) == 1){
        exit(1);
    }
    return 0;
}

# Client
#include "socket.h"

int main(){
    Socket socket(8080);

    // Client
    if(socket.Connect() == 1){
        exit(1);
    }
    if(socket.SendMessage("Hello World") == 1){
        exit(1);
    }
    return 0;
}
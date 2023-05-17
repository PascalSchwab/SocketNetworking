#include "socket.h"

void test(string message){
    std::cout << message << std::endl;
}

int main(){
    Socket socket(8080);

    // Server
    if(socket.Listen(test) == 1){
        exit(1);
    }
    return 0;
}
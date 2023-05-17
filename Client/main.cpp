#include "socket.h"

int main(){
    Socket socket(8080);

    // Client
    if(socket.Connect() == 1){
        exit(1);
    }
    if(socket.SendMessage("Moin") == 1){
        exit(1);
    }
    return 0;
}
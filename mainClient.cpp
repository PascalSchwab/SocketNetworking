#include "client.h"

int main(){
    Client client(8080, "127.0.0.1");
    if(client.Connect() == 1){
        exit(1);
    }
    client.SendMessage("Hello World");
    return 0;
}
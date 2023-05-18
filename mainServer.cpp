#include "server.h"

void callbackFunc(struct RecievedMessage* message){
    cout << message->message << endl;
}

int main(){
    Server server(8080, callbackFunc);
    if(server.Start() == 1){
        exit(1);
    }
    return 0;
}
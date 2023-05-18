# SocketNetworking
    Library for Socket Programming in C++
# Server
    #include "server.h"

    void callbackFunc(string message){
        cout << message << endl;
    }

    int main(){
        Server server(8080, callbackFunc);

        if(server.Start() == 1){
            exit(1);
        }
        
        return 0;
    }

# Client
    #include "client.h"

    int main(){
        Client client(8080, "127.0.0.1");

        if(client.Connect() == 1){
            exit(1);
        }

        client.SendMessage("Hello World");

        return 0;
    }

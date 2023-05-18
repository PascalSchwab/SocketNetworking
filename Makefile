all: rmbin makebin server client cleanbuild

server: mainServer.o server.o socket.o
	g++ mainServer.o server.o socket.o -o bin/server
mainServer.o: mainServer.cpp server.h
	g++ -c mainServer.cpp
server.o: server.cpp socket.h server.h
	g++ -c server.cpp

client: mainClient.o client.o socket.o
	g++ mainClient.o client.o socket.o -o bin/client
mainClient.o: mainClient.cpp client.h
	g++ -c mainClient.cpp
client.o: client.cpp socket.h client.h
	g++ -c client.cpp

socket.o: socket.cpp socket.h
	g++ -c socket.cpp

rmbin:
	rm -rf bin

makebin:
	mkdir bin

cleanbuild:
	rm -rf server.o socket.o client.o mainClient.o mainServer.o
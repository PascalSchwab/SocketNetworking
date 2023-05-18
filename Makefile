all: rmbin makebin server client cleanbuild

server: server.o socket.o
	g++ server.o socket.o -o bin/server
server.o: server.cpp socket.h
	g++ -c server.cpp

client: client.o socket.o
	g++ client.o socket.o -o bin/client
client.o: client.cpp socket.h
	g++ -c client.cpp

socket.o: socket.cpp socket.h
	g++ -c socket.cpp

rmbin:
	rm -rf bin

makebin:
	mkdir bin

cleanbuild:
	rm -rf server.o socket.o client.o
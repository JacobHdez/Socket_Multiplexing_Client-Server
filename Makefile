all: server client

server: server.o sockLib.o
	g++ server.o sockLib.o -o server

client: client.o sockLib.o
	g++ client.o sockLib.o -o client

server.o: server.cpp
	g++ -c server.cpp

client.o: client.cpp
	g++ -c client.cpp

sockLib.o: include/sockLib.cpp include/sockLib.h
	g++ -c include/sockLib.cpp

clean:
	rm *.o server client
#include "sockLib.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

// Socket function
int Socket( void ) {
	int s;

	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( s < 0 ) {
		perror( "[-] socket call failed" );
		exit( 1 );
	}
	cout << "[+] server socket is created." << endl;

	return s;
}

// Server functions
void initSockaddr( struct sockaddr_in *sockAddr, unsigned int port ) {
	memset( sockAddr, 0, sizeof( *sockAddr ) );

	sockAddr->sin_family = AF_INET;
	sockAddr->sin_port = htons( port );
	sockAddr->sin_addr.s_addr = htonl( INADDR_ANY );
}
void Bind( int &sockfd, struct sockaddr_in *sockAddr ) {
	int ret;

	ret = bind( sockfd, (struct sockaddr *)&(*sockAddr), sizeof( *sockAddr ) );
	if ( ret < 0 ) {
		perror( "[-] bind call failed" );
		close( sockfd );
		exit( 1 );
	}
	cout << "[+] bind to port " << htons( sockAddr->sin_port ) << "." << endl;
}
void Listen( int &sockfd, unsigned int max ) {
	int ret;

	ret = listen( sockfd, max );
	if ( ret < 0 ) {
		perror( "[-] listen call failed" );
		close( sockfd );
		exit( 1 );
	}
	cout << "[+] listening ..." << endl;
}
int Accept( int &sockfd ) {
	int newSockfd;

	newSockfd = accept( sockfd, NULL, NULL );
	if ( newSockfd < 0 ) {
		perror( "[-] accept call failed" );
		close( sockfd );
		exit(1);
	}
	cout << "[+] connection accepted.\n" << endl;

	return newSockfd;
}

// Client functions
void initSockaddr( struct sockaddr_in *sockAddr, const char *host , unsigned int port ) {
	memset( sockAddr, 0, sizeof( *sockAddr ) );

	sockAddr->sin_family = AF_INET;
	sockAddr->sin_port = htons( port );
	sockAddr->sin_addr.s_addr = inet_addr( host );
}
void Connect( int &sockfd, struct sockaddr_in *sockAddr ) {
	int ret;

	ret = connect( sockfd, (struct sockaddr *)&(*sockAddr), sizeof( *sockAddr ) );
	if ( ret < 0 ) {
		perror( "[-] connect call failed" );
		close( sockfd );
		exit(1);
	}
	cout << "[+] connected to server.\n" << endl;
}
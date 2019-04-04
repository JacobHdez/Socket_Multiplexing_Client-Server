#ifndef SOCKLIB_H
#define SOCKLIB_H

// Socket function
int Socket( void );

// Server functions
void initSockaddr( struct sockaddr_in *sockAddr, unsigned int port );
void Bind( int &sockfd, struct sockaddr_in *sockAddr );
void Listen( int &sockfd, unsigned int max );
int Accept( int &sockfd );

// Client functions
void initSockaddr( struct sockaddr_in *sockAddr, const char *host , unsigned int port );
void Connect( int &sockfd, struct sockaddr_in *sockAddr );

#endif // SOCKLIB_H
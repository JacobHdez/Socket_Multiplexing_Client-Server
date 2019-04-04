#include <iostream>
#include <cstring>
#include "include/sockLib.h"
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main(int argc, char const *argv[])
{
	if ( argc < 2 ) {
		cout << "<port>" << endl;
		return 0;
	}

	int s, sockfd;
	struct sockaddr_in server;

	s = Socket();
	initSockaddr( &server, atoi( argv[1] ) );
	Bind( s, &server );
	Listen( s, 2 );
	sockfd = Accept( s );

	char msg[128];
	int n;
	fd_set readSet;

	FD_ZERO( &readSet );

	bool flag = true;
	while ( flag ) {
		FD_SET( 0, &readSet );
		FD_SET( sockfd, &readSet );

		n = select( sockfd+1, &readSet, 0, 0, NULL );
		if ( n < 0 ) {
			perror("[-] select call failed");
			close( sockfd );
			close( s );
			exit( 1 );
		}
		else if ( n > 0 ) {
			if ( FD_ISSET( 0, &readSet ) ) {
				cin.getline( msg, 128, '\n' );
				if ( strlen(msg) == 0 ) {
					flag = false;
					continue;
				}
				n = write( sockfd, msg, strlen(msg) );
				if ( n < 0 ) {
					perror("[-] write call failed");
					close( sockfd );
					close( s );
					exit( 1 );
				}
			} // if ( FD_ISSET( 0, &readSet ) )
			if ( FD_ISSET( sockfd, &readSet ) ) {
				n = read( sockfd, msg, sizeof(msg) );
				if ( n < 0 ) {
					perror( "[-] read call failed" );
					close( sockfd );
					close( s );
					exit( 1 );
				}
				if ( n == 0 ){
					flag = false;
					continue;
				}
				msg[n] = '\0';
				cout << "Client: " << msg << endl;
			} // if ( FD_ISSET( sockfd, &readSet ) )
		}
	} // while ( flag )

	close( sockfd );
	close( s );
	cout << "[-] server closed." << endl;

	return 0;
}
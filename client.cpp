#include <iostream>
#include <cstring>
#include "include/sockLib.h"
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main(int argc, char const *argv[])
{
	if ( argc < 3 ) {
		cout << "<host> <port>" << endl;
		return 0;
	}

	int s;
	struct sockaddr_in server;

	s = Socket();
	initSockaddr( &server, argv[1], atoi( argv[2] ) );
	Connect( s, &server );

	char msg[128];
	int n;
	fd_set readSet;

	FD_ZERO( &readSet );

	bool flag = true;
	while ( flag ) {
		FD_SET( 0, &readSet );
		FD_SET( s, &readSet );

		n = select( s+1, &readSet, 0, 0, NULL );
		if ( n < 0 ) {
			perror("[-] select call failed");
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
				n = write( s, msg, strlen(msg) );
				if ( n < 0 ) {
					perror("[-] write call failed");
					close( s );
					exit( 1 );
				}
			} // if ( FD_ISSET( 0, &readSet ) )
			if ( FD_ISSET( s, &readSet ) ) {
				n = read( s, msg, sizeof(msg) );
				if ( n < 0 ) {
					perror( "[-] read call failed" );
					close( s );
					exit( 1 );
				}
				if ( n == 0 ){
					flag = false;
					continue;
				}
				msg[n] = '\0';
				cout << "Server: " << msg << endl;
			} // if ( FD_ISSET( s, &readSet ) )
		}
	} // while ( flag )

	close ( s );
	cout << "[-] disconnected." << endl;

	return 0;
}
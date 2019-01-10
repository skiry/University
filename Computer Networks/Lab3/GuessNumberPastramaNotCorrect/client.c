#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER "127.0.0.1"
   struct sockaddr_in server;
 	int slen = sizeof(server);
void play_client( int socket ) {
    char won = 0;

    uint16_t input;
    uint16_t tosend;
    uint16_t toreceive;

    while( !won ) {
        printf( "Choose a number: " );
        scanf( "%hu", &input );

        tosend = htons( input );
        sendto( socket, &tosend, sizeof(tosend), 0 , (struct sockaddr *) &server, slen);

        recvfrom( socket, &toreceive, sizeof(toreceive), 0, (struct sockaddr *) &server, slen );
        toreceive = ntohs( toreceive );

        if ( toreceive == 1 ) {
            won = 1;
            printf( "Congratulations! You won!\n" );
        }
        else if ( toreceive == 2 ) {
            printf( "The given number is way too large!\n" );
        }
        else {
            printf( "The given number is way too small!\n" );
        }
    }
 
    recvfrom(socket, &toreceive, sizeof(toreceive), 0, (struct sockaddr *) &server, &slen);
    toreceive = ntohs( toreceive );

    printf( "You had to guess %d times.\n", toreceive );

    close(socket);
}

int main(void) {
    int used_socket;
 
    used_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (used_socket < 0) {
        printf("Could not create the socket.\n");
        return 1;
    }
 
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
 
if (inet_aton(SERVER , &server.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
   
 
    play_client( used_socket );
 
    return 0;
}

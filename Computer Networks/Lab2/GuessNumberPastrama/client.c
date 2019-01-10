#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void play_client( int socket ) {
    char won = 0;

    uint16_t input;
    uint16_t tosend;
    uint16_t toreceive;

    while( !won ) {
        printf( "Choose a number: " );
        scanf( "%hu", &input );

        tosend = htons( input );
        send( socket, &tosend, sizeof(tosend), 0 );

        recv( socket, &toreceive, sizeof(toreceive), 0 );
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
 
    recv(socket, &toreceive, sizeof(toreceive), 0);
    toreceive = ntohs( toreceive );

    printf( "You had to guess %d times.\n", toreceive );

    close(socket);
}

int main(void) {
    int used_socket;
    struct sockaddr_in server;
 
    used_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (used_socket < 0) {
        printf("Could not create the socket.\n");
        return 1;
    }
 
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if (connect(used_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error connecting to the server.\n");
        return 2;
    }
 
    play_client( used_socket );
 
    return 0;
}

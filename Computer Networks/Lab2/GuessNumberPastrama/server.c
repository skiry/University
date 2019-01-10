#include <stdio.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

uint16_t number;
void serve_client( int ret_addr ) {
    srand( time( NULL ) );
    uint16_t tries = 0;
    char found = 0;

    printf( "The generated number is: %d.\n", number );

    uint16_t tosend;
    uint16_t toreceive;
    while ( !found ) {
        recv( ret_addr, &toreceive, sizeof(toreceive), MSG_WAITALL );
        toreceive = ntohs( toreceive );

        tries++;

        if ( toreceive == number ) {
            tosend = 1;
            found = 1;
        }
        else if ( toreceive > number ) {
            tosend = 2;
        }
        else {
            tosend = 0;
        }

        tosend = htons( tosend );
        send( ret_addr, &tosend, sizeof(tosend), 0);
    }

    tosend = htons( tries );
    send( ret_addr, &tosend, sizeof(tosend), 0 );

    close(ret_addr);
}

int main(void) {
    int used_socket;
    number = rand() % 100 + 1;
    struct sockaddr_in server, client;

    used_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (used_socket < 0) {
        printf("Error creating the socket.\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(used_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Bind error.\n");
        return 2;
    }

    listen(used_socket, 100);
    int client_size = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        int ret_addr = accept(used_socket, (struct sockaddr *) &client, &client_size);

        if ( fork() == 0 ) {
            serve_client( ret_addr );
        }
    }

    return 0;
}

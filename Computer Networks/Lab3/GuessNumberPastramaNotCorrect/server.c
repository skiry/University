#include <stdio.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

uint16_t number;
struct sockaddr_in server, client, si_other;
    int slen = sizeof(si_other);
void serve_client( int ret_addr ) {
    srand( time( NULL ) );
    uint16_t tries = 0;
    char found = 0;

    printf( "The generated number is: %d.\n", number );

    uint16_t tosend;
    uint16_t toreceive;
    while ( !found ) {
        recvfrom( ret_addr, &toreceive, sizeof(toreceive),0,&si_other,&slen);
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
        sendto( ret_addr, &tosend, sizeof(tosend), 0,(struct sockaddr*) &si_other, slen);
    }

    tosend = htons( tries );
    sendto( ret_addr, &tosend, sizeof(tosend), 0,(struct sockaddr*) &si_other, slen );

    close(ret_addr);
}

int main(void) {
    int used_socket;
    number = rand() % 100 + 1;
    

    used_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    int client_size = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {

        if ( fork() == 0 ) {
            serve_client( used_socket );
        }
    }

    return 0;
}

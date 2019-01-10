#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
 
int main(void) {
    // The socket we will use.
    int used_socket;
    // Here we need two sockaddr_in structures, for client as well.
    struct sockaddr_in server, client;
 
    // Create the socket, handle case when it can't be created.
    used_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (used_socket < 0) {
        printf("Error creating the socket.\n");
        return 1;
    }
 
    // Empty the sockaddr_in and set some values.
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
 
    // Attempt to bind the socket to the used sockaddr_in, handle failure.
    if (bind(used_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Bind error.\n");
        return 1;
    }
 
    // Start listening, store client size and clear the client sockaddr_in information.
    listen(used_socket, 5);
    int client_size = sizeof(client);
    memset(&client, 0, sizeof(client));
 
    printf("Server started up successfully.\n");
    // Keep running.
    while (1) {
        // Accept a connection.
        int ret_addr = accept(used_socket, (struct sockaddr *) &client, &client_size);
        printf("Accepted a new connection.\n");
 
        // Attempt to fork just after accept, so multiple clients can be served concurrently.
        if ( fork() == 0 ) {
            // Information related to the problem to be solved.
            uint16_t tosend;
            uint16_t toreceive;
 
            // Note that the sent and received information has to be converted.
            // Conversion between network byte to host byte.
            // https://linux.die.net/man/3/ntohs
            // ntohs = network to host (short / uint16_t)
            // htons = host to network (short / uint16_t)
 
            // Receive the data.
            recv(ret_addr, &toreceive, sizeof(toreceive), MSG_WAITALL);
 
            toreceive = ntohs( toreceive );
            tosend = htons( toreceive / 5 );
 
            // Send back the response.
            send(ret_addr, &tosend, sizeof(tosend), 0);
 
            // Close the connection to the client.
            close(ret_addr);
        }
    }
 
    return 0;
}

// client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(void) {
    // The socket we will use.
    int used_socket;
    // Here we require just one sockaddr_in, for the server.
    struct sockaddr_in server;
 
    // Attempt to create the socket, handle failure.
    used_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (used_socket < 0) {
        printf("Could not create the socket.\n");
        return 1;
    }
 
    // Clear the server sockaddr_in data and set some values.
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    // Attempt to connect to the server, handle failure.
    if (connect(used_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error connecting to the server.\n");
        return 2;
    }
 
    printf("Client started up successfully.\n");
    // Data related to the problem to be solved.
    uint16_t tosend;
    uint16_t toreceive;
 
    // Note that the sent and received information has to be converted.
    // Conversion between network byte to host byte.
    // https://linux.die.net/man/3/ntohs
    // ntohs = network to host (short / uint16_t)
    // htons = host to network (short / uint16_t)
 int input;
 scanf("%d",&input);   
 tosend = htons( input);

 
    // Send the data.
    send(used_socket, &tosend, sizeof(tosend), 0);
    // Receive the response.
    recv(used_socket, &toreceive, sizeof(toreceive), 0);
 
    toreceive = ntohs( toreceive );
    printf("Received response: %d.\n", toreceive);
 
    // Close the connection to the server.
    close(used_socket);
 
    return 0;
}

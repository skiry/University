#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
 
#define BUFSZ 40000
int main(void) {
    // The socket we will use.
    int used_socket;
	int wS;
    char torcv[BUFSZ], tosnd[BUFSZ];
    char sendThis[] = "GET /HTTP/1.0\n\n";
char saveAll[2000] = "";
    // Here we need two sockaddr_in structures, for client as well.
    struct sockaddr_in server, client, withSite;
 	//struct hostent *gethostbyname(const char *name);
struct hostent *pHostInfo;// = (struct hostent *)malloc(sizeof(struct hostent));
    // Create the socket, handle case when it can't be created.
    used_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (used_socket < 0) {
        printf("Error creating the socket.\n");
        return 1;
    }
setsockopt(used_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1},sizeof(int));
 
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
            recv(ret_addr, &torcv, sizeof(torcv), MSG_WAITALL);



 printf("Received: %s\n", torcv);

 pHostInfo = gethostbyname(torcv);

printf("Ip ADDRESS->%s\n",pHostInfo->h_addr);
fflush(stdout);




wS = socket(AF_INET, SOCK_STREAM, 0);
    if (wS < 0) {
        printf("Could not create the socket.\n");
        return 1;
    }
 printf("Created the website socket: %s\n", torcv);


    // Clear the server sockaddr_in data and set some values.
    memset(&withSite, 0, sizeof(withSite));
    //memcpy(&withSite, pHostInfo->h_addr,pHostInfo->h_length);
    withSite.sin_port = htons(80);
    withSite.sin_family = AF_INET;
    //withSite.sin_addr.s_addr = inet_addr(pHostInfo->h_addr);
    bcopy((char*)pHostInfo->h_addr, (char*)&withSite.sin_addr, pHostInfo->h_length);
 
    // Attempt to connect to the server, handle failure.
    if (connect(wS, (struct sockaddr *) &withSite, sizeof(withSite)) < 0) {
        printf("Error connecting to the website.\n");
        return 2;
    }
		printf("Connected to the received website.\n");

	send(wS, &sendThis, sizeof(sendThis), 0);
		char * buffer = malloc(sizeof(char) * 101);
	int r;
	while ((r = recv(wS, buffer, 100, 0)) > 0)
	{
		buffer[r] = 0;
		send(ret_addr, buffer, strlen(buffer), 0);
	}

	free(buffer);
 
            // Send back the response.
            //send(ret_addr, &saveAll, sizeof(saveAll), 0);
 
            // Close the connection to the client.
	    close(wS);
            close(ret_addr);

        }
    }
 
    return 0;
}

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>


void process(int c)
{
	if (c < 0)
	{
		perror("Error connecting to client!\n");
		exit(1);
	}

	char website[500];
	if (recv(c, &website, sizeof(website), MSG_WAITALL) < 0)
	{
		perror("Error receiving website!\n");
		exit(1);
	}

	int domainSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (domainSocket < 0)
	{
		perror("Error creating socket!\n");
		exit(1);
	}

	struct hostent * host = gethostbyname(website);
	if (host == 0)
	{
		perror("Unknown host!\n");
		exit(1);
	}

	struct sockaddr_in domainServer;
	memset(&domainServer, 0, sizeof(domainServer));
	domainServer.sin_family = AF_INET;
	domainServer.sin_port = htons(80);
	bcopy((char*)host->h_addr, (char*)&domainServer.sin_addr, host->h_length);

	if (connect(domainSocket, (struct sockaddr*)&domainServer, sizeof(domainServer)) < 0)
	{
		perror("Error connecting to website!\n");
		exit(1);
	}
	
	char request[] = "GET / HTTP/1.0\n\n";
	if (send(domainSocket, &request, strlen(request), 0) < 0)
	{
		perror("Error sending request to website!\n");
		exit(1);
	}

	char * buffer = malloc(sizeof(char) * 101);
	int r;
	while ((r = recv(domainSocket, buffer, 100, 0)) > 0)
	{
		buffer[r] = 0;
		send(c, buffer, strlen(buffer), 0);
	}

	free(buffer);
	
	close(domainSocket);
	close(c);
}

int main()
{
	int tcp = socket(PF_INET, SOCK_STREAM, 0);
	if (tcp < 0)
	{
		perror("Error creating TCP socket!\n");
		exit(1);
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(tcp, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("Bind error!\n");
		exit(1);
	}

	listen(tcp, 5);

	while (1)
	{
		struct sockaddr_in client;
		memset(&client, 0, sizeof(client));

		int l = sizeof(client);

		int c = accept(tcp, (struct sockaddr*)&client, &l);

		if (fork() == 0)
		{
			process(c);
		}
	}

	return 0;	
}


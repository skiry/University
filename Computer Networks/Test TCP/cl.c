#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	int c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0)
	{
		perror("Error creating TCP socket!\n");
		exit(1);
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("Error connecting to server!\n");
		exit(1);
	}

	char website[500];
	printf("Enter website: ");
	scanf("%s", website);

	if (send(c, &website, sizeof(website), 0) < 0)
	{
		perror("Error sending website!\n");
		exit(1);
	}

	char * buffer = malloc(sizeof(char) * 101);
	int r;
	do
	{
		r = recv(c, buffer, 100, 0);
		if (r > 0)
		{
			buffer[r] = 0;
			printf("%s", buffer);
			if (r < 100)
				break;
		}
	} while(r > 0);	

	free(buffer);
	close(c);

	return 0;
}


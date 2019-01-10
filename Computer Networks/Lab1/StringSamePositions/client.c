#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

 

int main() {

       int c;

       struct sockaddr_in server;

       uint16_t suma;
       char *a, *b;
       a = malloc(20*sizeof(char));
       b = malloc(20*sizeof(char));

 

       c = socket(AF_INET, SOCK_STREAM, 0);

       if (c < 0) {

              printf("Eroare la crearea socketului client\n");

              return 1;

       }

 

       memset(&server, 0, sizeof(server));

       server.sin_port = htons(1324);

       server.sin_family = AF_INET;

       server.sin_addr.s_addr = inet_addr("127.0.0.1");

 

       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {

              printf("Eroare la conectarea la server\n");

              return 1;

       }

 

       printf("First string : ");

       scanf("%s", a);

       printf("Second string : ");

       scanf("%s", b);

	char character;
       send(c, a, 20*sizeof(char), 0);

       send(c, b, 20*sizeof(char), 0);

       recv(c, &character, sizeof(char), 0);
       recv(c, &suma, sizeof(suma), 0);
       suma = ntohs(suma);
	if(suma)
       printf("Caracterul cel mai comun pe aceleasi pozitii este %c si apare de %d ori pe pozitii comune\n",character, suma);
	else printf("Nu e niciun caracter comun");
	free(a);
	free(b);
       close(c);

}


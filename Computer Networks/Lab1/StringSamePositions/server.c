#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

 

int main() {

       int s;

       struct sockaddr_in server, client;

       int c, l;

 

       s = socket(AF_INET, SOCK_STREAM, 0);

       if (s < 0) {

              printf("Eroare la crearea socketului server\n");

              return 1;

       }

 

       memset(&server, 0, sizeof(server));

       server.sin_port = htons(1324);

       server.sin_family = AF_INET;

       server.sin_addr.s_addr = INADDR_ANY;

 

       if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {

              printf("Eroare la bind\n");

              return 1;

       }

 

       listen(s, 5);

 

       l = sizeof(client);

       memset(&client, 0, sizeof(client));

 

       while (1) {

	       uint16_t suma=0;
	       char *a, *b, character;
	       a = malloc(20*sizeof(char));
	       b = malloc(20*sizeof(char));
	       c = accept(s, (struct sockaddr *) &client, &l);
	       int vect[26] = {0};
              printf("S-a conectat un client.\n");

              // deservirea clientului

              recv(c, a, 20*sizeof(char), MSG_WAITALL);

              recv(c, b, 20* sizeof(char), MSG_WAITALL);

		for(int i=0;i<strlen(a)&&i<strlen(b);++i){
			if(tolower((unsigned char)a[i]) ==  tolower((unsigned char)b[i]))
				if(++vect[tolower((unsigned char)a[i])-'a'] > suma){
				        suma = vect[tolower((unsigned char)a[i])-'a'];
			       		character = a[i];
				}		
		}
              suma = htons(suma);
		send(c,&character, sizeof(char), 0);
              send(c, &suma, sizeof(suma), 0);
		free(a);
		free(b);
              close(c);

              // sfarsitul deservirii clientului;

       }

}


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

              uint16_t a, b, suma=0;

              c = accept(s, (struct sockaddr *) &client, &l);

              printf("S-a conectat un client.\n");

              // deservirea clientului
		char word[10];
              recv(c, word, sizeof(word), MSG_WAITALL);


		for(int i=0;i<strlen(word);++i)
			switch(tolower((unsigned char)word[i])){
				case 'a':case 'e':case 'i':case 'o':case 'u':
					continue;
				default: ++suma;break;
			}
              suma = htons(suma);

              send(c, &suma, sizeof(suma), 0);

              close(c);

              // sfarsitul deservirii clientului;

       }

}


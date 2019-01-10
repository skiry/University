#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

 

int main() {

       int c;

       struct sockaddr_in server;

       int* array, *array2, n,m,*result,nm;

 

       c = socket(AF_INET, SOCK_STREAM, 0);

       if (c < 0) {

              printf("Eroare la crearea socketului client\n");

              return 1;

       }

 

       memset(&server, 0, sizeof(server));

       server.sin_port = htons(9999);

       server.sin_family = AF_INET;

       server.sin_addr.s_addr = inet_addr("127.0.0.1");

 

       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {

              printf("Eroare la conectarea la server\n");

              return 1;

       }

 

       printf("n = ");

       scanf("%d", &n);

	array=malloc(n*sizeof(int));



       for(int i=0;i<n;++i)
	       scanf("%d",array+i);


       printf("m = ");

       scanf("%d", &m);

	array2=malloc(m*sizeof(int));

       for(int i=0;i<m;++i)
	       scanf("%d",array2+i);



       n = htonl(n);

       m = htonl(m);


       send(c, &n, sizeof(n), 0);
	n=ntohl(n);
       for(int i=0;i<n;++i)
       {
	       int nr =  htonl(array[i]);
	       send(c, &nr, sizeof(nr), 0);
       }


       send(c, &m, sizeof(m), 0);
	m=ntohl(m);
       for(int i=0;i<m;++i)
     {
	     int nr = htonl(array2[i]);
	     send(c, &nr, sizeof(nr),0);
     }




       recv(c, &nm, sizeof(nm), 0);
       nm = ntohl(nm);


       printf("%d elemente sunt la fel\n",nm);


       result=malloc(nm*sizeof(int));
       printf("Elementele asemanatoare sunt:");

	for(int i=0;i<nm;++i){

	recv(c, result+i, sizeof(int),0);

	result[i] = ntohl(result[i]);

	printf(" %d",result[i]);
	}	

      
	free(result);
	free(array2);
	free(array);
       close(c);

}

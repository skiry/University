#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

 

int main() {

       int s;

       struct sockaddr_in server, client;

     	int c,l;

 

       s = socket(AF_INET, SOCK_STREAM, 0);

       if (s < 0) {

              printf("Eroare la crearea socketului server\n");

              return 1;

       }

 

       memset(&server, 0, sizeof(server));

       server.sin_port = htons(9999);

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

              int n,m,*a1,*a2,nr,*res,cnt=0;

              c = accept(s, (struct sockaddr *) &client, &l);

              printf("S-a conectat un client.\n");

              // deservirea clientului

              recv(c, &n, sizeof(n), MSG_WAITALL);

              n = ntohl(n);


		a1=malloc(n*sizeof(int));

	      for(int i = 0;i<n;++i){
		      recv(c,a1+i,sizeof(int), MSG_WAITALL);

		      a1[i]=ntohl(a1[i]);
	      }


              recv(c, &m, sizeof(m), MSG_WAITALL);

              m = ntohl(m);

		a2=malloc(m*sizeof(int));

		for(int i = 0;i<m;++i){
			recv(c,a2+i,sizeof(int),MSG_WAITALL);
			a2[i]=ntohl(a2[i]);
		}

		for(int i=0;i<n;++i){
			int check=0;
			for(int j=0;j<m;++j)
				if(a1[i]==a2[j])
					check=1;
			if(check) ++nr;
		}

		res=malloc(nr*sizeof(int));

		for(int i=0;i<n;++i){
			int check=0;
			for(int j=0;j<m;++j)
				if(a1[i]==a2[j])
					check=1;
			if(check) res[cnt++]=a1[i];
		}

		nr=htonl(nr);
              send(c, &nr, sizeof(nr), 0);
	      nr=ntohl(nr);
	      for(int i=0;i<nr;++i)
	      {
		      res[i]=htonl(res[i]);
		      send(c,res+i,sizeof(int),0);
	      }

	      free(a1);
	      free(a2);
	      free(res);

              close(c);

              // sfarsitul deservirii clientului;

       }

}

 

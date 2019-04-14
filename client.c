#include <winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int main()
{
 WSADATA WSa;
      WSAStartup(MAKEWORD(2,0),&WSa);
      SOCKADDR_IN S;
      SOCKET ClientS;
      ClientS=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
      S.sin_family=AF_INET;
      S.sin_addr.s_addr = inet_addr("127.0.0.1");
      S.sin_port=htons(20);
      connect(ClientS,(SOCKADDR *)&S,sizeof(S));
      char nomp[100],prixp[100],nom[100];
      recv(ClientS,nomp,100,0);
      recv(ClientS,prixp,100,0);
      printf("%s %s \n",nomp,prixp);
      printf("donner votre nom \n");
      scanf("%s",nom);
      send(ClientS,nom,sizeof(nom),0);
      while(1){
            char prc[100];
          printf("donner prix \n");
          scanf("%s",prc);
          send(ClientS,prc,sizeof(prc),0);
          recv(ClientS,prc,sizeof(prc),0);
          printf("%s %s \n",nomp,prc);
      }
}

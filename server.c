#include <winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
char nom[100],prix[100];
pthread_mutex_t mutex_stdout = PTHREAD_MUTEX_INITIALIZER;
void *traitement(void *arg){
SOCKET sock=(SOCKET *)arg;
  char nomClient[100];
recv(sock,nomClient,100,0);
while(1){
        char prixClient[100];
    recv(sock,prixClient,100,0);
    pthread_mutex_lock (& mutex_stdout);
    strcpy(prix,prixClient);
    pthread_mutex_unlock (& mutex_stdout);
   send(sock,prix,sizeof(prix),0);
   printf("%s %s \n",nomClient,prix);
}
}
int main(){
    printf("donner le produit \n");
    scanf("%s",nom);
     printf("donner prix \n");
    scanf("%s",prix);
    WSADATA WSa;
      WSAStartup(MAKEWORD(2,0),&WSa);
      SOCKADDR_IN S;
      S.sin_family=AF_INET;
      S.sin_addr.s_addr =htonl(INADDR_ANY);
      S.sin_port=htons(20);
      SOCKET sock;
      sock=socket(AF_INET,SOCK_STREAM,0);
      bind(sock, (SOCKADDR *)&S, sizeof(S));
      listen(sock,10);
      pthread_t pthread;
      while(1){
      SOCKADDR_IN Client;
      SOCKET acceptC;
      int N=sizeof(Client);
      acceptC=accept(sock,(SOCKADDR *)&Client,&N);
       send(acceptC,nom,sizeof(nom),0);
       send(acceptC,prix,sizeof(prix),0);
     pthread_create(&pthread,NULL,&traitement,(void *)acceptC);
      }
}

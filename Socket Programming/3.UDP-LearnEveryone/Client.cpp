#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void printError(char *msg){

    perr(msg);

    exit(0);
}

int main(int argc , char *argv[]){
    
    int sock , length  ,n;

    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *ht;
    char buffer[512];
    
    if(argc ! =3){
        printf("Usage : Server Port \n");
        exit(0);
    }


    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0){
        
        printError("Opening Socket ");
    }


    server.sin_family = AF_INET;
    ht = gethostbyname(argv[1]);


    if(ht ==0){
        printError("Unknown host");
    }

    bcopy((char* ht)->h_addr ,(char* )&server.sin_addr,ht->h_length);
  
    server.sin_port = htons(atoi(argv[2]));

    length = sizeof(struct sockaddr_in);

    printf("Enter Message:");
    bzero(buffer ,512);
    fgets(buffer,512,stdin);

    n = sendto(sock ,buffer , strlen(buffer),0 ,&server,length);

    if( n< 0){

        printError("Send to");
    }

    n = recvfrom(sock ,buffer , 512,0 ,&from,&length);

    if( n< 0){

        printError("recvfrom");
    }

    write(1 ,"Recieved an ACK:" ,17);
    write(1 ,buffer,17);







    

  


    return 0;


}  







































































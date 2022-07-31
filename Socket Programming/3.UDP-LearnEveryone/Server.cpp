#include<stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


void printError(char *msg){

    perr(msg);

    exit(0);
}

int main(int argc , char *argv[]){
    
    int sock , length ,fromlen ,n;

    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];
    
    if(argc < 2){
        fprintf(stderr ,"No Port Error\n");
        exit(0);
    }


    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0){
        
        printError("Opening Socket ");
    }

    length = sizeof(server);
    bzero(&server ,length);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if(bind(sock ,(struct sockaddr *)&server ,length) <0)
    {
        printError("Binding");
    }

    fromlen = sizeof(struct sockaddr_in);

    while(1){

         n = recvfrom(sock ,buf ,1024 , 0 ,(struct sockaddr *)&from ,&fromlen);

         if(n <0){

             printError("recvFrom");
         }

         write(1 ,"Recieved a datagram" ,30);
         write(1 ,buf ,n);
         n = sendto(sock ,"Recieved your Message\n" ,22 , 0 ,(struct sockaddr*)&from , &fromlen);
         
         if(n <0){

             printError("recvFrom");
         }

    }


    return 0;


}  







































































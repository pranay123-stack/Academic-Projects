#include <iostream>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <netdb.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>







#include<cstring>

int main(int argc , char* argv[]){

    int sockfd ,newsockfd ,portno ,n;
    struct sockaddr_in serv_addr ,client_addr;

    char buffer[1024];

    socklen_t len;

    if(argc <2){
        printf("provide required command line inputs as <filename.c> <server_IP_addr><portno>");
        exit(1);
    }

    portno = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd <0){

        printf("ERROR in opening socket");
        exit(1);
    }
    // build the structure for server address
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr =INADDR_ANY;
    serv_addr.sin_port = htons(portno);


    if(bind(sockfd , (struct sockaddr*) &serv_addr,sizeof(serv_addr)) <0){

        printf("ERROR in binding socket");
    }

     listen(sockfd ,5);

     len = sizeof(client_addr);

     newsockfd = accept(sockfd ,(struct sockaddr*)&client_addr ,&len);

     if(newsockfd <0){
          printf("ERROR in accepting request.../");
     }


     while(1){
          bzero(buffer ,1024);
        //   Now read some data from the client...
        n = read(newsockfd ,buffer ,1024);

        if(n <0){

            printf("ERROR in reading ...");
            exit(1);
        }

        printf("\nClient -->%s" ,buffer)

        bzero(buffer ,1024);

        fgets(buffer ,1024 ,stdin);

        n = write(newsockfd ,buffer ,1024);

        if(n <0){

            printf("ERROR in writing");
            exit(1);
        }

        if(! strncmp("bye" ,buffer ,3))
        {
             break;
        }
     }
      
      close(newsockfd);
      close(sockfd);




    
}
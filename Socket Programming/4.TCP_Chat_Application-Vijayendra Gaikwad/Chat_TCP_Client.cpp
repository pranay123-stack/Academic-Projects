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

    int sockfd ,portno ,n;
    struct sockaddr_in serv_addr ;

    char buffer[1024];

    socklen_t len;

    if(argc <3){
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
    serv_addr.sin_addr.s_addr =inet_addr(argv[1]);
    serv_addr.sin_port = htons(portno);


    if(connect(sockfd , (struct sockaddr*) &serv_addr,sizeof(serv_addr)) <0){

        printf("Connection failed...!");
    }


     while(1){
          bzero(buffer ,1024);
        

      

        fgets(buffer ,1024 ,stdin);

        n = write(sockfd ,buffer ,strlen(buffer));

        if(n <0){

            printf("ERROR in writing");
            exit(1);
        }

             bzero(buffer ,1024);
      
    //   read back from the server
        n = read(sockfd ,buffer ,1024);

        if(n <0){

            printf("ERROR in reading ...");
            exit(1);
        }
         
         printf("\nServer-->%s" ,buffer);


        if(! strncmp("bye" ,buffer ,3))
        {
             break;
        }
     }
      
      close(sockfd);




    
}
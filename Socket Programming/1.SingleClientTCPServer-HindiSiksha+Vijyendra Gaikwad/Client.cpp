#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<cstring>
using namespace std;


int main(){

    string ipAdddress = "127.0.0.1";
    int port = 54000;



// Create socket
int client = socket(AF_INET, SOCK_STREAM, 0);
if(client == -1){

    cerr<<"Can't create socket";
    return 0;
}




// fill sockaddr_in structure
sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET, ipAdddress.c_str(), &hint.sin_addr);




// connect to server
int conResult = connect(client ,(sockaddr*)&hint ,sizeof(hint));

if(conResult == -1) {

    cerr<<"Can't connect";
    return 0;
}

// do while loop:send and recv data
char buf[4096];
string msg;

do{
  
//   prompt user to send something
cout<<">";
getline(cin ,msg);

if(msg.length() >0){

    //send the message back to server
    memset(buf, 4096 ,0);
    int sent = send(client , msg.c_str() ,msg.size() +1 ,0);

    if(sent !=-1){
        // Wait for response
        memset(buf ,4096 ,0);
       int bytesRecieved = recv(client ,buf ,4096 ,0);
       if(bytesRecieved >0){

            // print the message to console
            cout<<"<server>"<<string(buf , 0,bytesRecieved)<<endl;

       }
    }
}

}while(msg.length() > 0);




// close the socket

close(client);

 return 0;

 
}
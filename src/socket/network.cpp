#include"network.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include<iostream>
#include<cstring>

std::string Exception::getMessage(){
    return this->message;
}

TCPServer::TCPServer(int port,std::string address)
:port(port){
 
    if ((this->servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw new NetworkException("SOCKET Error: could not create basic socket");
    }

    memset(&this->ServAddr,0,sizeof(this->ServAddr));

    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(address.c_str());
    ServAddr.sin_port = htons(port);

    
    if (bind(this->servSock, (struct sockaddr *) &this->ServAddr, sizeof(this->ServAddr)) < 0) {
        throw new NetworkException("SOCKET Error: Failed to bind a socket");
    }

    if (::listen(this->servSock, MAXPENDING) < 0) {
        throw new NetworkException("SOCKET Error: Failed to Listen");
    }
}

void TCPServer::listen(){

    struct sockaddr_in ClntAddr;     /* Client address */
    socklen_t clntLen= (socklen_t)sizeof(ClntAddr);
    int clntSock;                    /* Socket descriptor for client */
    //@todo Dummy Logic Depedency Inject Socket Handler
    for (;;) {
       if ((clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, &clntLen)) < 0) {
           std::cout<<"Failed to fetch"<<std::endl;
       }

       send(clntSock, "12345\n", 6, 0);

       std::cout << "Handling client %s\n" << inet_ntoa(ClntAddr.sin_addr) << std::endl;
       close(clntSock);
    }
}

TCPServer::~TCPServer(){
 close(this->servSock);
}
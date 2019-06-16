#include"network.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <string>
#include <thread>

std::string Exception::getMessage(){
    return this->message;
}

TCPServer::TCPServer(int port,std::string address, std::shared_ptr<ConnectionHandler> c):port(port),c(c){
 
    if ((this->servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw NetworkException(std::string("SOCKET Error: could not create basic socket"));
    }

    memset(&this->ServAddr,0,sizeof(this->ServAddr));

    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(address.c_str());
    ServAddr.sin_port = htons(port);

    
    if (bind(this->servSock, (struct sockaddr *) &this->ServAddr, sizeof(this->ServAddr)) < 0) {
        throw NetworkException(std::string("SOCKET Error: Failed to bind a socket"));
    }

    if (::listen(this->servSock, MAXPENDING) < 0) {
        throw NetworkException(std::string("SOCKET Error: Failed to Listen"));
    }
}

void TCPServer::listen(){

    struct sockaddr_in ClntAddr;     /* Client address */
    socklen_t clntLen = (socklen_t)sizeof(ClntAddr);
    int clntSock;                    /* Socket descriptor for client */

    for (;;) {
    
       if ((clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, &clntLen)) < 0) {
           std::cout<<"Failed to fetch"<<std::endl;
           continue;
       }
       std::cout << "Client Socket: " << clntSock << std::endl;
       std::cout << "Handling client: " << inet_ntoa(ClntAddr.sin_addr) << std::endl;
       send(clntSock, "WELCOME", 8, 0);

       std::thread handleConnectionThread(callHandler, this->c, clntSock);
       handleConnectionThread.detach();
    }
}

TCPServer::~TCPServer(){
 close(this->servSock);
}

int callHandler(std::shared_ptr<ConnectionHandler> c, int socketId){
    return c->handle(socketId);
}        

#include"Network.h"

#include <sys/socket.h>
#include <arpa/inet.h>

Exception::getMessage(){
    return this->message;
}

TCPServer::TCPServer(int port,std::string address)
:port(port){
 
    if ((this->sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw NetworkException("SOCKET Error: could not create basic socket");
    }

    memset(&this->ServAddr,0,size_of(this->ServAddr))

    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(address);
    ServAddr.sin_port = htons(port);

    
    if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
        throw NetworkException("SOCKET Error: Failed to bind a socket");
    }

    if (listen(servSock, MAXPENDING) < 0) {
        throw NetworkException("SOCKET Error: Failed to Listen")
    }
}
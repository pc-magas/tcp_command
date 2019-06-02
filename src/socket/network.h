#ifndef HTTP_SOCKET
#define HTTP_SOCKET

#include<string>
#include <sys/socket.h>
#include <arpa/inet.h>

class Exception{
    public:
    Exception(std:string message):message(message);
    std::string getMessage()
    private:
    std::string message;
}

class NetworkException: public Exception{}

class TCPServer{
    public:
    TCPServer(unsinged int port,std::string address);
    ~TCPServer(unsinged int port);
    void listen();
    void close();
    private:
    int port;
    //Socket file Descriptor
    int sockfd;
    struct sockaddr_in ServAddr;
}

class　HTTP_REQUEST{
    public:

}

#endif
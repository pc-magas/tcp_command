#ifndef HTTP_NETWORK
#define HTTP_NETWORK

#include<string>
#include <sys/socket.h>
#include <arpa/inet.h>

//Dummy Value to be changed
#define MAXPENDING = 5;

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
    private:
    int port;
    //Socket file Descriptor
    int servSock;
    struct sockaddr_in ServAddr;
}
#endif
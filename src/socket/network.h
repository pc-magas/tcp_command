#ifndef HTTP_NETWORK
#define HTTP_NETWORK

#include<string>
#include <arpa/inet.h>

//Dummy Value to be changed
#define MAXPENDING = 5;

class Exception {
    public:
    Exception(std::string message):message(message){}
    std::string getMessage();
    private:
    std::string message;
};

class NetworkException:public Exception {
    public:
    NetworkException(){};
    ~NetworkException(){};
};

class TCPServer{
    public:
    TCPServer(int port,std::string address);
    ~TCPServer();
    void listen();
    private:
    int port;
    //Socket file Descriptor
    int servSock;
    struct sockaddr_in ServAddr;
};
#endif
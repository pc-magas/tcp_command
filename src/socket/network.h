#ifndef HTTP_NETWORK
#define HTTP_NETWORK

#include<string>
#include <arpa/inet.h>

//Dummy Value to be changed
#define MAXPENDING 5

class Exception {
    public:
    Exception(std::string message):message(message){}
    std::string getMessage();
    private:
    std::string message;
};

class NetworkException:public Exception {
    public:
    NetworkException(std::string message) : Exception(message) {}
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

//A generic way to handle Network Connections
class ConnectionHandler{
    public:
    ConnectionHandler()
    virtual void handle(int socketid);
}
#endif
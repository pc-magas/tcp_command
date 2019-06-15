#ifndef HTTP_NETWORK
#define HTTP_NETWORK

#include <string>
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

//A generic way to handle Network Connections
class ConnectionHandler {
    public:
    /**
    * @return 0 Close Connection 1 do not close
    */
    virtual int handle(int socketid) = 0;
};

class TCPServer {
    public:
        TCPServer(int port, std::string address, ConnectionHandler *c);
        ~TCPServer();
        void listen();
    private:
        int port;
        //Socket file Descriptor
        int servSock;
        struct sockaddr_in ServAddr;
        ConnectionHandler *c = NULL;
};


#endif
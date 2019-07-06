#ifndef HTTP_NETWORK
#define HTTP_NETWORK

#include <memory>
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
    protected:
        virtual bool handleReceivedData(int socketid, const char* receivedBuffer, int recvSize) = 0;
    
    public:
        ConnectionHandler(int buffLen):buffLen(buffLen){};
        ~ConnectionHandler(){};
        bool handle(int socketid);
        virtual void disconnect(int socketid) = 0;
    
    private:
        const int buffLen;
};

/**
 * Because the only job is to call the handle method of ConnectionHandler,
 * I assume there's no need for a class.
 * 
 * Is is used to call the handler in a std::thread.
 */
void callHandler(std::shared_ptr<ConnectionHandler> c, int sockerId);        

class TCPServer {
    public:
        TCPServer(int port, std::string address, std::shared_ptr<ConnectionHandler> connection);
        ~TCPServer();
        void listen();
    private:
        int port;
        //Socket file Descriptor
        int servSock;
        struct sockaddr_in ServAddr;
        std::shared_ptr<ConnectionHandler> connection;
};


#endif
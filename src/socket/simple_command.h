#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include"network.h"
#include<string>

class SimpleCommandHandler:public ConnectionHandler{
    public:
    SimpleCommandHandler(int readBufferSize):buffLen(readBufferSize){};
    ~SimpleCommandHandler(){};
    void handle(int socketid);

    private:
    std::string readLine(int socketid);
    void sendResult(int socketid, std::string result);
    const int buffLen;
}

#endif
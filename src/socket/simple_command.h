#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include"network.h"
#include<string>

class SimpleCommandHandler:public ConnectionHandler{
    public:
    SimpleCommandHandler(int readBufferSize, CommandParser* commandParser):buffLen(readBufferSize),parser(commandParser){};
    ~SimpleCommandHandler(){};
    int handle(int socketid);

    private:
    std::string readLine(int socketid);
    void sendResult(int socketid, std::string result);
    const int buffLen;
    CommandParser* parser;
};
#endif
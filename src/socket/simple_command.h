#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include"network.h"
#include<string>

class CommandParser{
    private:
        std::string commandBuff;
    public:
        std::string getCommand()
        std::string addData()
}

class SimpleCommandHandler:public ConnectionHandler{
    public:
    SimpleCommandHandler(int readBufferSize, CommandParser commandParser):buffLen(readBufferSize),parser(commandParser){};
    ~SimpleCommandHandler(){};
    void handle(int socketid);

    private:
    std::string readLine(int socketid);
    void sendResult(int socketid, std::string result);
    const int buffLen;
    const CommandParser parser;
}
#endif
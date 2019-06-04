#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include"network.h"
#include<map>
#include<string>

class CommandParser{
    private:
        std::map<int,std::string> commandBuff;
    public:
        std::string getCommand(int socketid);
        void addData(int socketid, const char* data, int length);
};

class SimpleCommandHandler:public ConnectionHandler{
    public:
    SimpleCommandHandler(int readBufferSize, CommandParser* commandParser):buffLen(readBufferSize),parser(commandParser){};
    ~SimpleCommandHandler(){};
    int handle(int socketid);

    private:
    std::string readLine(int socketid);
    void sendResult(int socketid, std::string result);
    const int buffLen;
    const CommandParser* parser;
};
#endif
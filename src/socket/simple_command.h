#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include<string>
#include<map>

// Project defined libraries
#include"network.h"
#include"../tools/command_parser.h"


class SimpleCommandHandler:public ConnectionHandler{
    public:
    SimpleCommandHandler(int readBufferSize, CommandParser *commandParser):buffLen(readBufferSize),parser(commandParser){};
    ~SimpleCommandHandler(){};
    bool handle(int socketid);
    void disconnect(int socketid);

    private:
    void sendResult(int socketid, std::string result);
    const int buffLen;
    CommandParser* parser;
    bool processCommand(std::string command, int socketid);
};
#endif
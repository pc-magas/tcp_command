#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#define EMPTY_COMMAND ""

#include<string>
#include<map>

// Project defined libraries
#include"network.h"
#include"../tools/command_parser.h"


class SimpleCommandHandler:public ConnectionHandler{
    protected:
        bool handleReceivedData(int socketid, const char* receivedBuffer, int recvSize);

    public:
        SimpleCommandHandler(int readBufferSize, CommandParser *commandParser):ConnectionHandler(readBufferSize),parser(commandParser){};
        ~SimpleCommandHandler(){};
        void disconnect(int socketid);

    private:
        void sendResult(int socketid, std::string result);
        CommandParser* parser;
        bool processCommand(std::string command, int socketid);
};
#endif
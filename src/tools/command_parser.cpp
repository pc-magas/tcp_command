#include "command_parser.h"
#include <string>

#ifdef DEBUG
#include<iostream>
#endif

void CommandParser::addData(int socketid, const char* data, int length){
    #ifdef DEBUG
     std::cout << "Adding Data " << data << std::endl;
    #endif //DEBUG
   commandBuff[socketid].append(data,length);
}

std::string CommandParser::getCommand(int socketid){

    std::string& buffer = commandBuff[socketid];
    std::size_t pos = buffer.find('\n');

    if (pos==std::string::npos){
        return "";
    }

    std::string fetchedCommand = buffer.substr(0,pos);
    buffer = buffer.substr(pos+1);

    #ifdef DEBUG
     std::cout << "Command Received" << fetchedCommand << std::endl;
    #endif //DEBUG
    

    return fetchedCommand;
}

void CommandParser::clearBuff(int socketId){
    this->commandBuff.erase(socketId);
}
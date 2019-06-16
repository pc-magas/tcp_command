#include "command_parser.h"
#include<string>
#include<iostream>

void CommandParser::addData(int socketid, const char* data, int length){
    this->commandBuff[socketid].append(data,length);
}

std::string CommandParser::getCommand(int socketid){
    std::size_t pos = this->commandBuff[socketid].find('\n');

    if (pos==std::string::npos){
        return "";
    }

    std::string fetchedCommand = this->commandBuff[socketid].substr(0,pos);
    #ifdef DEBUG
        std::cout << "Fetched Command: " << fetchedCommand << std::endl;
        std::cout << "BUFFER BEFORE: " << this->commandBuff[socketid] << std::endl; 
    #endif
    
    this->commandBuff[socketid] = this->commandBuff[socketid].substr(pos+1);

    #ifdef DEBUG
        std::cout << "BUFFER After: " << this->commandBuff[socketid] << std::endl;
    #endif

    return fetchedCommand;
}
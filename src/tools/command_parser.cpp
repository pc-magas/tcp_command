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
    // std::cout << "Before: " << this->commandBuff[socketid] << std::endl;
    this->commandBuff[socketid] = this->commandBuff[socketid].substr(pos+1);
    // std::cout << "After: " << this->commandBuff[socketid] << std::endl;
    return fetchedCommand;
}
#include "command_parser.h"
#include <string>

#ifdef DEBUG
#include<iostream>
#endif

void CommandParser::addData(int socketid, const char* data, int length){
    #ifdef DEBUG
        std::cout << "ADD DATA: ";
        std::cout << data << " " << length << std::endl;
    #endif

    this->commandBuff[socketid].append(data,length);
    #ifdef DEBUG
        std::cout << "Resulted Buffer: " << data << std::endl;
    #endif
}

std::string CommandParser::getCommand(int socketid){
    std::size_t pos = this->commandBuff[socketid].find('\n');

    if (pos==std::string::npos){
        #ifdef DEBUG
            std::cout << "DEBUG: New line not found" << std::endl;
        #endif
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
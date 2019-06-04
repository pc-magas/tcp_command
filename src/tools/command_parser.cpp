#include "command_parser.h"
#include<string>

void CommandParser::addData(int socketid, const char* data, int length){
    this->commandBuff[socketid].append(data,length);
}

std::string CommandParser::getCommand(int socketid){
    std::size_t pos=this->commandBuff[socketid].find('\n');
    std::string fetchedCommand=this->commandBuff[socketid].substr(0,pos);
    this->commandBuff[socketid]=this->commandBuff[socketid].substr(pos);
    return fetchedCommand;
}
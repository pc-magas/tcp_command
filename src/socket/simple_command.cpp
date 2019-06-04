#include "simple_command.h"
#include<string>

std::string SimpleCommandHandler::readLine(int socketid){
    int recvSize=0;
    char buffer[this->buffLen];

    memset(&buffer,'\0',this->buffLen*sizeof(char));
    //reCeive a Byte less in order each received data to be a string (Initialized as an empty String with \0 encding char)
    while ((recvSize = recv(socketid, buffer, this->buffLen-1, 0)) > 0) {
        this->parser->addData(socketid,(cost char*) buffer,strlen(buffer));
        memset(buffer,'\0',this->buffLen*sizeof(char)); //Reset Data in order to avoid Garbage
	}

    return this->parser->getCommand();
}

void SimpleCommandHandler::sendResult(int socketid, std::string result){
    send(clntSock,result.c_str(), result.length() + 1, 0);
}

void SimpleCommandHandler::handle(int socketid){
    std::string command = this->readLine(socketid);

    if(command.compare('exit')){
        this->sendResult(socketid,"Thank You Very Much\nExiting\n");
        return 0;
    } else {
        this->sendResult(socketid,"Wrong Command\n");
    }

    return 1;
}

void CommandParser::addData(int socketid, const char* data, int length){
    this->commandBuff[socketid].append(data,length);
}

std::string CommandParser::getCommand(int socketid){
    std::size_t pos=this->commandBuff[socketid].find('\n');
    std::string fetchedCommand=this->commandBuff[socketid].substr(0,pos);
    this->commandBuff[socketid]=this->commandBuff[socketid].substr(pos);
    return fetchedCommand;
}
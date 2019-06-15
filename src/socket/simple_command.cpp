#include "simple_command.h"
#include<string>
#include<cstring>
#include<iostream>

std::string SimpleCommandHandler::readLine(int socketid){
    int recvSize=0;
    char buffer[this->buffLen];

    memset(&buffer,'\0',this->buffLen*sizeof(char));
    //reCeive a Byte less in order each received data to be a string (Initialized as an empty String with \0 encding char)
    while ((recvSize = recv(socketid, buffer, this->buffLen-1, 0)) > 0) {
        this->parser->addData(socketid,(const char*) buffer,strlen(buffer));
        memset(buffer,'\0',this->buffLen*sizeof(char)); //Reset Data in order to avoid Garbage
	}

    return this->parser->getCommand(socketid);
}

void SimpleCommandHandler::sendResult(int socketid, std::string result){
    send(socketid, result.c_str(), result.length() + 1, 0);
}

int SimpleCommandHandler::handle(int socketid){
    std::string command = this->readLine(socketid);
    std::cout << "Command Sent: " << command << std::endl;
    if(command.compare("exit") == 0){
        this->sendResult(socketid,"Thank You Very Much\nExiting\n");
        return 0;
    } else {
        this->sendResult(socketid,"Wrong Command\n");
    }

    return 1;
}
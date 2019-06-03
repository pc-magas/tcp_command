#include "telnet.h"
#include<string>

std::string SimpleCommandHandler::readLine(int socketid){
    int recvSize=0;
    char buffer[this->bufflen] 

    memset(&buffer,'\0',this->bufflen*sizeof(char));
    while ((recvSize = recv(socketid, buffer, this->bufflen, 0)) > 0) {
        this->parser->addData(buffer);
        memset(&buffer,'\0',this->bufflen*sizeof(char)); //Reset Data in order to avoid Garbage
	}

    return this->parser->getCommand();
}

void SimpleCommandHandler::sendResult(int socketid, std::string result){
    send(clntSock,result::c_str(), result.length() + 1, 0);
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
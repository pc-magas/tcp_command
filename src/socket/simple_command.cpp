#include "simple_command.h"
#include <string>
#include <cstring>
#include <iostream>
#include <map>

#include <unistd.h>

std::string SimpleCommandHandler::readLine(int socketid){
    int recvSize=0;
    char buffer[this->buffLen];

    memset(&buffer,'\0',this->buffLen*sizeof(char));
    //reCeive a Byte less in order each received data to be a string (Initialized as an empty String with \0 encding char)
    while ((recvSize = recv(socketid, buffer, this->buffLen-1, 0)) > 0) {
        this->parser->addData(socketid,(const char*) buffer, recvSize);
        #ifdef DEBUG
            std::cout << "DEBUG BUFFER: " << buffer << "RECEIVED SIZE: " << recvSize << std::endl;
        #endif

        memset(buffer,'\0',this->buffLen*sizeof(char)); //Reset Data in order to avoid Garbage
	}

    #ifdef DEBUG
        std::cout << "DEBUG Loop BROKEN" << std::endl;
    #endif

    return this->parser->getCommand(socketid);
}

void SimpleCommandHandler::sendResult(int socketid, std::string result){
    std::cout << "Socket length data" << result.length() << std::endl;
    send(socketid, result.c_str(), result.length(), 0);
}

bool SimpleCommandHandler::handle(int socketid){
    std::string command = this->readLine(socketid);
    std::clog << "Command Sent: " << command << std::endl;

    //In order to ensure that all data have been sent we close the socket later
    if(this->shouldSocketToBeClosed(socketid)){
        this->disconnect(socketid);
        return false;
    }
    
    this->toBeTerminated[socketid]=false;

    if(command.compare("exit") == 0){
        this->sendResult(socketid,"Thank You Very Much\nExiting\n");
        #ifdef DEBUG
          std::cout << "Command Exit" << std::endl;
        #endif
        this->toBeTerminated[socketid]=true;
    } else {
        this->sendResult(socketid,"Wrong Command\n");
    }

    return true;
}

void SimpleCommandHandler::disconnect(int socketid){
    this->parser->clearBuff(socketid);
    close(socketid);
    this->toBeTerminated.erase(socketid);
}

 bool SimpleCommandHandler::shouldSocketToBeClosed(int socketid){
    auto socketExists = this->toBeTerminated.find(socketid);

    if(socketExists!=this->toBeTerminated.end()){
        return this->toBeTerminated[socketid];
    }

    return false;
 }
#include "simple_command.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <unistd.h>


void SimpleCommandHandler::sendResult(int socketid, std::string result){
    std::cout << "Socket length data" << result.length() << std::endl;
    send(socketid, result.c_str(), result.length(), 0);
}

bool SimpleCommandHandler::handle(int socketid){
    #ifdef DEBUG
        std::cout << "Handling Socket: " << socketid << std::endl;
    #endif

    std::vector<char> storage(buffLen);
    char *const buffer = storage.data();
    int recvSize=0;

    while ((recvSize = ::recv(socketid, buffer, this->buffLen-1, 0)) > 0) {
        parser->addData(socketid,(const char*) buffer, recvSize);
        #ifdef DEBUG
            std::cout << "DEBUG BUFFER: " << buffer << "RECEIVED SIZE: " << recvSize << std::endl;
        #endif
        // memset(buffer,'\0',this->buffLen*sizeof(char)); //Reset Data in order to avoid Garbage
        std::string command = EMPTY_COMMAND;
        do {
            command = parser->getCommand(socketid);
            if(!this->processCommand(command,socketid)) return false;
        } while(command != EMPTY_COMMAND);
	}
    
    return true;
}

void SimpleCommandHandler::disconnect(int socketid){
    #ifdef DEBUG
        std::cout << "Closing socket: " << socketid << std::endl;
    #endif
    this->parser->clearBuff(socketid);
    ::close(socketid);
}

bool SimpleCommandHandler::processCommand(std::string command, int socketid) {
    #ifdef DEBUG
        std::cout << "On socket: " << socketid << " is handled the following command: " << command << std::endl;
    #endif
    if(command == EMPTY_COMMAND){
        return true; //Do not process empty commands
    } else if(command == "exit") {
        this->sendResult(socketid,"Thank You Very Much\nExiting\n");
        #ifdef DEBUG
          std::cout << "Command Exit: " << std::endl;
        #endif
        this->disconnect(socketid);
        return false;
    } else if (command == "hello") {
        this->sendResult(socketid,"Hello\n");
    } else {
        this->sendResult(socketid,"Wrong Command\n");
    }

    return true;
}
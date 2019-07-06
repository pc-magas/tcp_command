#include "simple_command.h"
#include <string>
#include <iostream>
#include <map>

#include <unistd.h>


void SimpleCommandHandler::sendResult(int socketid, std::string result){
    std::cout << "Socket length data" << result.length() << std::endl;
    send(socketid, result.c_str(), result.length(), 0);
}

bool SimpleCommandHandler::handleReceivedData(int socketid, const char* receivedBuffer, int recvSize) {

        parser->addData(socketid,(const char*) receivedBuffer, recvSize);
        #ifdef DEBUG
            std::cout << "DEBUG BUFFER: " << receivedBuffer << "RECEIVED SIZE: " << recvSize << std::endl;
        #endif

        std::string command = EMPTY_COMMAND;
        do {
            command = parser->getCommand(socketid);
            if(!this->processCommand(command, socketid)) return false;
        } while(command != EMPTY_COMMAND);

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
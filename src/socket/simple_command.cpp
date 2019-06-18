#include "simple_command.h"
#include<string>
#include<cstring>
#include <unistd.h>

#include<iostream>

#include <thread>
#include <chrono>

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

int SimpleCommandHandler::handle(int socketid){
    std::string command = this->readLine(socketid);
    std::cout << "Command Sent: " << command << std::endl;
    int ok=0;
    if(command.compare("exit") == 0){
        this->sendResult(socketid,"Thank You Very Much\nExiting\n");
        #ifdef DEBUG
          std::cout << "Command Exit" << std::endl;
        #endif
    } else {
        this->sendResult(socketid,"Wrong Command\n");
        ok=1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    close(socketid);
    return ok;
}
#include<iostream>
#include<string>

#include "socket/network.h"
#include "socket/simple_command.h"
#include "tools/command_parser.h"

int main(){
    try{
        CommandParser p;
        SimpleCommandHandler c(10,&p);
        TCPServer server(7070, "127.0.0.1", &c);
        server.listen();
    }catch(Exception e){
        std::cout<< e.getMessage();
        return -1;
    }
    return 0;
}
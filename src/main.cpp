#include<iostream>
#include<string>
#include<memory>

#include "socket/network.h"
#include "socket/simple_command.h"
#include "tools/command_parser.h"

int main(){
    try {
        CommandParser p;
        std::shared_ptr<ConnectionHandler> c (new SimpleCommandHandler(10,&p));
        TCPServer server(7070, "127.0.0.1", c);
        server.listen();
    } catch(Exception e) {
        std::cerr<< e.getMessage();
        return 1;
    }
    return 0;
}
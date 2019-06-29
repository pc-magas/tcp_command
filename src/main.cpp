#include<iostream>
#include<string>
#include<memory>
#include<unistd.h>

#include "socket/network.h"
#include "socket/simple_command.h"
#include "tools/command_parser.h"

int main(int argc, char **argv){

    std::string address;
    std::string port;
    int argVal=0;

    while ((argVal = getopt (argc, argv, "h:p:")) != -1){
        std::cout << optarg << std::endl;
        switch (argVal) {
        case 'h':
            address = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case '?':
            std::cerr << "Unknown Parameters" << std::endl;
        default:
            abort();
        }
    }

    try {
        CommandParser p;
        std::shared_ptr<ConnectionHandler> connectionHandler (new SimpleCommandHandler(10,&p));
        std::clog << "Trying to establish a server in " << address << ":"<< port << std::endl;
        TCPServer server(std::atoi(port.c_str()), address, connectionHandler);
        server.listen();
    } catch(Exception e) {
        std::cerr<< e.getMessage();
        return 1;
    }
    return 0;
}
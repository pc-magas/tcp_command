#include<iostream>
#include<string>

#include"socket/network.h"

int main(){
    try{
        TCPServer server(7070,"127.0.0.1");
        server.listen();
    }catch(Exception e){
        std::cout<< e.getMessage();
        return -1;
    }
    return 0;
}
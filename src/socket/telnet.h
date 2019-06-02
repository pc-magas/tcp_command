#ifndef NETWORK_TELNET
#define NETWORK_TELNET

#include"network.h"
#include<string>

class TelnetHandler:public ConnectionHandler{
    public:
    TelnetHandler(){};
    ~TelnetHandler(){};
    void handle(int socketid);

    private:
    std::string readLine(int socketid);
    void sendResult(int socketid, std::string result);
}

#endif
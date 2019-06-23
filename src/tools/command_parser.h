#ifndef COMMANDPARSER
#define COMMANDPARSER

#include<string>
#include<map>

class CommandParser{
    private:
        std::map<int,std::string> commandBuff;
    public:
        std::string getCommand(int socketid);
        void addData(int socketid, const char* data, int length);
        void clearBuff(int socketId);
};

#endif
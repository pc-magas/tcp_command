#include <cxxtest/TestSuite.h>
#include<string>

#include "../../src/socket/simple_command.h"

class TestCommandExecuter: public CxxTest::TestSuite{

    public:
        void testSetGetCommandNoFetch(){
            CommandParser p;
            const char data[5] ={'d','r','f','a','p'};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand();
            
        }

}
#include <cxxtest/TestSuite.h>
#include<string>

#include "../../src/tools/command_parser.h"

class TestCommandParser: public CxxTest::TestSuite{

    public:
        void testSetGetCommandNoFetch(){
            CommandParser p;
            const char data[5] ={'d','r','f','a','p'};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
        }

        void testGetCommand(){
            CommandParser p;
            const char data[5] ={'e','x','i','t','\n'};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
        }

        void testGetCommandMultiple(){
            CommandParser p;
            const char data[10] ={'e','x','i','t','\n','e','x','i','t','\n'};
            int length=10;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
            
            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
        }

};
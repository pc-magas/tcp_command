#include <cxxtest/TestSuite.h>
#include <string>
#include <iostream>

#include "../../src/tools/command_parser.h"

class TestCommandParser: public CxxTest::TestSuite{

    public:
        /**
         * Testing if not a command has been completed,
         * not to fetch it
         */
        void testSetGetCommandNoFetch(){
            CommandParser p;
            const char data[5] ={'d','r','f','a','p'};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
        }

        /**
         * Tests when no command provided then no command is received
         */
        void testGetCommandEmpty(){
            CommandParser p;
            const char data[5] ={};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
        }

        /**
         * Scenario when sucessfulle a simplge command is fetched
         */
        void testGetCommand(){
            CommandParser p;
            const char data[5] ={'e','x','i','t','\n'};
            int length=5;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
        }

        /**
         * Test when a command is provided in chunks
         */
        void getTestCommandCHunked(){
            CommandParser p;
            const char chunk_one[2]={'e','x'};
            int length_one=2;

            const char chunk_two[1]={'i'};
            int length_two=1;

            const char chunk_three[2]={'i','x'};
            int length_three=2;

            p.addData(5,chunk_one,length_one);
            p.addData(5,chunk_two,length_two);
            p.addData(5,chunk_three,length_three);

            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
        }

        /**
         * Test when more than one commands are being provided
         */
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

        /**
         * Test when more comanda are being asked that have been provided
         */
        void testgetCommandMultipleEndLine(){
            CommandParser p;
            const char data[10] ={'e','x','i','t','\n','e','x','i','t','\n'};
            int length=10;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
            
            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
        }

        void testCommonUsageScenario(){

            std::cout << "Test Multiple Command Fetch" << std::endl;

            CommandParser p;
            const char data[10] ={'e','x','i','t','\n','e','x','i','t','\n'};
            int length=10;
            
            p.addData(5,data,length);
            std::string command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");
            
            const char chunk_one[2]={'e','x'};
            int length_one=2;

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
            p.addData(5,chunk_one,length_one);

            const char chunk_two[1]={'i'};
            int length_two=1;
            p.addData(5,chunk_two,length_two);

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");

            const char chunk_three[3]={'t','\n','e'};
            int length_three=3;
            p.addData(5,chunk_three,length_three);

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"exit");

            command=p.getCommand(5);
            TS_ASSERT_EQUALS(command,"");
        }
};
/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_TestCommandExecuter_init = false;
#include "/home/pc_magas/Kwdikas/C++/telnet/tests/CommandExecuter/testCommandExecuter.h"

static TestCommandExecuter suite_TestCommandExecuter;

static CxxTest::List Tests_TestCommandExecuter = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestCommandExecuter( "./tests/CommandExecuter/testCommandExecuter.h", 5, "TestCommandExecuter", suite_TestCommandExecuter, Tests_TestCommandExecuter );

static class TestDescription_suite_TestCommandExecuter_testSetGetCommandNoFetch : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestCommandExecuter_testSetGetCommandNoFetch() : CxxTest::RealTestDescription( Tests_TestCommandExecuter, suiteDescription_TestCommandExecuter, 8, "testSetGetCommandNoFetch" ) {}
 void runTest() { suite_TestCommandExecuter.testSetGetCommandNoFetch(); }
} testDescription_suite_TestCommandExecuter_testSetGetCommandNoFetch;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

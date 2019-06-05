CC=g++
CFLAGS_DBG="-enable-pretty-printing"
TEST_BUILD_PATH="./build/tests"
BUILD_PATH="./build"
TESTS_SRC_PATH="./tests"
SRC_PATH=""

test_command_parser_gen:
	cxxtestgen --error-printer -o ${TESTS_SRC_PATH}/CommandParser/runner.cpp  ./tests/CommandParser/testCommandParser.h

test_command_parser: test_command_parser_gen
	g++ -o ${TEST_BUILD_PATH}/commandExecuter ${TESTS_SRC_PATH}/CommandParser/runner.cpp ./src/tools/command_parser.cpp

test_command_parser_run:
	
GDB=gdb
DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CCFLAGS =-DDEBUG
	RUNPATH =${GDB}
else
    CCFLAGS=-DNDEBUG
	RUNPATH=""
endif

CPP=g++ ${CCFLAGS}
TESTGEN=cxxtestgen
CFLAGS_DBG="-enable-pretty-printing"
TEST_BUILD_PATH="./build/tests"
BUILD_PATH="./build"
TESTS_SRC_PATH="./tests"
SRC_PATH=""

# NORMAL TARGETS


# RUN TESTS

test_command_parser_gen:
	${TESTGEN} --error-printer -o ${TESTS_SRC_PATH}/CommandParser/runner.cpp  ./tests/CommandParser/testCommandParser.h

test_command_parser_build: test_command_parser_gen
	${CPP} -o ${TEST_BUILD_PATH}/commandParser ${TESTS_SRC_PATH}/CommandParser/runner.cpp ./src/tools/command_parser.cpp

test_command_parser_run: test_command_parser_build
	${RUNPATH} ./build/tests/commandParser


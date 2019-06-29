GDB=gdb
DEBUG ?= 0
FORCE_SHELL ?= 1
HOST ?=127.0.0.1
PORT ?=7070

ifeq ($(DEBUG), 1)
    CCFLAGS =-DDEBUG
	RUNPATH =${GDB}
else
    CCFLAGS=-DNDEBUG
	RUNPATH=/bin/sh -c
endif

ifeq (${FORCE_SHELL}, 1)
	RUNPATH=/bin/sh -c
endif

CPP=g++ ${CCFLAGS} -std=c++11
TESTGEN=cxxtestgen
CFLAGS_DBG=""
TEST_BUILD_PATH="./build/tests"
BUILD_PATH=./build/release
TESTS_SRC_PATH="./tests"
SRC_PATH=""

# NORMAL TARGETS

build_commandParser: ./src/tools/command_parser.cpp ./src/tools/command_parser.h
	${CPP} -Wall -g -c ./src/tools/command_parser.cpp -o ${BUILD_PATH}/command_parser.o

build_network: ./src/socket/network.cpp ./src/socket/network.h
	${CPP} -Wall -g -c ./src/socket/network.cpp -o ${BUILD_PATH}/network.o

build_simpleCommand: ./src/socket/simple_command.cpp ./src/socket/simple_command.h
	${CPP} -Wall -g -c ./src/socket/simple_command.cpp -o ${BUILD_PATH}/simple_command.o

build: build_simpleCommand build_commandParser build_network ./src/main.cpp
	${CPP} -pthread -Wall -o ${BUILD_PATH}/server ${BUILD_PATH}/command_parser.o ${BUILD_PATH}/network.o ${BUILD_PATH}/simple_command.o ./src/main.cpp
run: build
	${RUNPATH} ${BUILD_PATH}/server -h ${HOST} -p ${PORT}

# RUN TESTS

test_command_parser_gen:
	${TESTGEN} --error-printer -o ${TESTS_SRC_PATH}/CommandParser/runner.cpp  ./tests/CommandParser/testCommandParser.h

test_command_parser_build: test_command_parser_gen build_commandParser
	${CPP} -o ${TEST_BUILD_PATH}/commandParser ${TESTS_SRC_PATH}/CommandParser/runner.cpp ${BUILD_PATH}/command_parser.o

test_command_parser_run: test_command_parser_build
	${RUNPATH} ./build/tests/commandParser 
	#./build/tests/commandParser

clean:
	find ./build ! -name '.gitkeep' -type f -exec rm -f {} + && find ./tests ! -name *.h -type f -exec rm -f {} +
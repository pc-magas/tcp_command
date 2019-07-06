HOST ?=127.0.0.1
PORT ?=7070

CCFLAGS:=-pthread -Wall -std=c++11
DEBUG_FLAGS=-g -DDEBUG
CPP=g++
TESTGEN=cxxtestgen
TEST_BUILD_PATH="./build/tests"
BUILD_PATH=./build/release
TESTS_SRC_PATH="./tests"
DEBUGER=gdb

# Flag definition
.PHONY: default

debug: FLAGS:=${CCFLAGS} ${DEBUG_FLAGS}
run: FLAGS:=${CCFLAGS}

default: run

# NORMAL TARGETS

debug: clean build
	${DEBUGER} --args ${BUILD_PATH}/server -h ${HOST} -p ${PORT}

build_commandParser: ./src/tools/command_parser.cpp ./src/tools/command_parser.h
	${CPP} ${FLAGS} -c ./src/tools/command_parser.cpp -o ${BUILD_PATH}/command_parser.o

build_network: ./src/socket/network.cpp ./src/socket/network.h
	${CPP} ${FLAGS} -c ./src/socket/network.cpp -o ${BUILD_PATH}/network.o

build_simpleCommand: ./src/socket/simple_command.cpp ./src/socket/simple_command.h
	${CPP} ${FLAGS} -c ./src/socket/simple_command.cpp -o ${BUILD_PATH}/simple_command.o

build: build_simpleCommand build_commandParser build_network ./src/main.cpp
	${CPP} ${FLAGS} -o ${BUILD_PATH}/server ${BUILD_PATH}/command_parser.o ${BUILD_PATH}/network.o ${BUILD_PATH}/simple_command.o ./src/main.cpp

run: build
	${BUILD_PATH}/server -h ${HOST} -p ${PORT}

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
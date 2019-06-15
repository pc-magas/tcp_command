GDB=gdb
DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CCFLAGS =-DDEBUG
	RUNPATH =${GDB}
else
    CCFLAGS=-DNDEBUG
	RUNPATH="/bin/sh -c"
endif

CPP=g++ ${CCFLAGS}
TESTGEN=cxxtestgen
CFLAGS_DBG=""
TEST_BUILD_PATH="./build/tests"
BUILD_PATH="./build/release"
TESTS_SRC_PATH="./tests"
SRC_PATH=""

# NORMAL TARGETS

build_commandParser: ./src/tools/command_parser.cpp ./src/tools/command_parser.h
	${CPP} -Wall -g -c ./src/tools/command_parser.cpp -o ${BUILD_PATH}/command_parser.o


# RUN TESTS

test_command_parser_gen:
	${TESTGEN} --error-printer -o ${TESTS_SRC_PATH}/CommandParser/runner.cpp  ./tests/CommandParser/testCommandParser.h

test_command_parser_build: test_command_parser_gen build_commandParser
	${CPP} -o ${TEST_BUILD_PATH}/commandParser ${TESTS_SRC_PATH}/CommandParser/runner.cpp ${BUILD_PATH}/command_parser.o

test_command_parser_run: test_command_parser_build
	# ${RUNPATH} ./build/tests/commandParser
	./build/tests/commandParser

clean:
	find ./build ! -name '.gitkeep' -type f -exec rm -f {} + && find ./tests ! -name *.h -type f -exec rm -f {} +
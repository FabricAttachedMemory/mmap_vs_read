# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS = --std=c++11 -Wall -W -Wfatal-errors -lbenchmark -lpthread -O2

SRC_DIR = ./src
# # the build target executable:
# # SRC = $(wildcard ./cpp/*.cpp)
SRC = ./src/readBlock.cpp ./src/readMmap.cpp ./src/runBench.cpp ./src/measures.cpp
# INCLUDES = -I /usr/include/hayia -I /usr/local/include
# # SRC = ./cpp/*.cpp
OBJ = $(SRC:.cpp=.o)

BLOCKREAD_TARGET = ./runBlockRead.cpp $(SRC_DIR)/readBlock.cpp
MMAP_TARGET = ./runMmap.cpp $(SRC_DIR)/readMmap.cpp

blockread:
	$(CC) $(CXXFLAGS) -o runBlockRead $(BLOCKREAD_TARGET)

mmapread:
	$(CC) $(CXXFLAGS) -o runMmap $(MMAP_TARGET)

all: blockread mmapread

runbech: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

clean :
	-rm ./src/*.o ./runbench ./runBlockRead ./runMmap
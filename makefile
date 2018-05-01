# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -W -Wfatal-errors -std=c++11

# the build target executable:
# SRC = $(wildcard ./cpp/*.cpp)
SRC = ./cpp/readBlock.cpp ./cpp/readMmap.cpp ./cpp/runBench.cpp 
OBJ = $(SRC:.cpp=.o)

all: clean runbech

runbech: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean :
	-rm ./cpp/*.o ./runbech
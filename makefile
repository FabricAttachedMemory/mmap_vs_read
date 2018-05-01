# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -W -Wfatal-errors -std=c++11

# the build target executable:
SRC = $(wildcard ./cpp/*.cpp)
OBJ = $(SRC:.cpp=.o)

runbech: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
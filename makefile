
# we are defining the compiler which is g++ for C++ program
CC = g++


# compiler flags are defined below
  #  -g flag is used to adds debugging information to the executable file
  #  -Wall flag turn on most compiler warnings in the file
CFLAGS  = -g -std=c++14

# Here is the target and the output 
#the build target
TARGET = avltree
OUTPUT = avltree

all: build

build: 
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(OUTPUT)

#cleaning the output
clean:
	$(RM) -r $(OUTPUT)
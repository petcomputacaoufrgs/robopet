# a simple makefile to demonstrate simplectest
# http://simplectest.sf.net/
# modified by lfzawacki
# this file is in the public domain :>

#choose your compiler
CC = g++

OBJ = point
OBJ_TESTS = $(OBJ:=Test)

FLAGS = -Wno-write-strings#-Wall uncomment to get warnings

all: $(OBJ_TESTS)

run: all
	./*Test

%Test: ../%.o %Test.cpp
	$(CC) -o $@ $^ $(FLAGS)

clean:
	-rm *.o *.exe

.PHONY: all clean

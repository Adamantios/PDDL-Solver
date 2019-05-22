CC=g++
CPPFLAGS=-g -Wall -Wextra -std=c++11

INCLUDE=-I./lib/ -I../Parser/include/

LDLIBS=-L./lib/ -lPDDLParser

SRCS=main.cpp

all: planner

planner: main.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) -o Planner $(SRCS) $(LDLIBS)

clean:
	$(RM) -rfv Planner

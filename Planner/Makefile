CC=g++
CPPFLAGS=-g -Wall -Wextra -std=c++11

INCLUDE=-Iinclude/ -I./lib/ -I../Parser/include/

LDLIBS=-L./lib/ -lPDDLParser

SRCS=main.cpp src/ParserController.cpp

all: planner

planner: $(SRCS)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o Planner $(SRCS) $(LDLIBS)

clean:
	$(RM) -rfv Planner

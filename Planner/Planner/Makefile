CC=g++
CPPFLAGS=-g -Wall -Wextra -std=c++11

INCLUDE=-I./Lib/ -I../../Parser/include/

LDLIBS=-L./Lib/ -lPDDLParser

SRCS=Planner.cpp

all: planner

planner: Planner.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) -o Planner $(SRCS) $(LDLIBS)

clean:
	$(RM) -rfv Planner

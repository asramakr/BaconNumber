# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o ActorNode.o MovieNode.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

# UnionFind.hpp Movie.h ActorNode.h ActorEdge.h

ActorGraph.o: ActorGraph.h 

ActorNode.o: ActorNode.h 

MovieNode.o: MovieNode.h

#MovieNodePtrComp.o: MovieNodePtrComp.h

clean:
	rm -f pathfinder *.o core*


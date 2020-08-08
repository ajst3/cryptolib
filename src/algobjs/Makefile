
.DEFAULT_GOAL := all

CPPFLAGS = -Wall -c
CXX = g++
INCLUDES = -I../../include

all: algorithm

algorithm: blowfish.o textmanager.o

.cpp.o:
	$(CXX) $(CPPFLAGS) $(INCLUDES) $^

clean:
	rm -f *.o

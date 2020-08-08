
.DEFAULT_GOAL := all

CPPFLAGS = -Wall -c
CXX = g++
INCLUDES = -I../../include

all: algorithm

algorithm: blowfish.o textmanager.o
	ar rcs libalgobjs.a $^

.cpp.o:
	$(CXX) $(CPPFLAGS) $(INCLUDES) $^

clean:
	rm -f *.o libalgobjs.a

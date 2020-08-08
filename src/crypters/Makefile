
.DEFAULT_GOAL := all

CPPFLAGS = -Wall -c
CXX = g++
INCLUDES = -I../../include

all: crypters

crypters: encrypter.o decrypter.o

.cpp.o:
	$(CXX) $(CPPFLAGS) $(INCLUDES) $^

clean:
	rm -f *.o

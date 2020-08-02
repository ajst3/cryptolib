
.DEFAULT_GOAL := algorithms

CPPFLAGS = -Wall -c
CXX = g++

algorithms: blowfish.o textmanager.o

blowfish.o: blowfish.cpp blowfish.hpp
	$(CXX) $(CPPFLAGS) $^

textmanager.o: textmanager.cpp textmanager.hpp
	$(CXX) $(CPPFLAGS) $^

clean:
	rm -f *.o

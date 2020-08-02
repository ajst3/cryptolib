
CPPFLAGS = -Wall
CXX = g++
INCLUDES = algobjs/*.o

algorithms:
	$(MAKE) -C algobjs

tester: algorithms tester.cpp
	$(CXX) $(CPPFLAGS) -I algobjs $(INCLUDES) tester.cpp -o $@


CPPFLAGS = -Wall
CXX = g++
LIBDIR = -L../src/algobjs -L../src/crypters
LIBS = -lalgobjs -lcrypters
INCLUDES = -I../include

algorithms:
	$(MAKE) -C ../src/algobjs

crypter:
	$(MAKE) -C ../src/crypters

testblowfish: algorithms crypter testblowfish.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDES) testblowfish.cpp -o $@ $(LIBDIR) $(LIBS)

clean:
	rm -f testblowfish

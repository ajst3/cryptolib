
CPPFLAGS = -Wall
CXX = g++
LIBDIR = -L..
LIBS = -lcryptolib
INCLUDES = -I../include
OBJECTS = testCBC testblowfish

.cpp:
	$(MAKE) -C ..
	$(CXX) $(CPPFLAGS) $(INCLUDES) $^ -o $@ $(LIBDIR) $(LIBS)

clean:
	rm -f $(OBJECTS)

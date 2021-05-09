
CPPFLAGS = -Wall
CXX = g++
LIBDIR = -L../install/lib
LIBS = -lcryptolib -lpthread
INCLUDES = -I../install/include
OBJECTS = testCBC testblowfish

.cpp:
	$(CXX) $(CPPFLAGS) $(INCLUDES) $^ -o $@ $(LIBDIR) $(LIBS)

clean:
	rm -f $(OBJECTS)

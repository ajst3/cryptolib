
blowfishtest: blowfish.cpp textmanager.cpp textmanager.hpp blowfish.hpp
	g++ -Wall $^ -o $@

blowfish.o: blowfish.cpp textmanager.cpp textmanager.hpp blowfish.hpp
	g++ -Wall $^ -o $@

clean:
	rm -f *.o
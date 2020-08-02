
algorithms:
	$(MAKE) -C /algobjs

tester: algorithms
	g++ -Wall -I /algobjs /algobjs/algorithms.o -o $^

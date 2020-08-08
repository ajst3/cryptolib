
.DEFAULT_GOAL := all

all: algorithms crypter
	ar rcs libcryptolib.a src/algobjs/*.o src/crypters/*.o

algorithms:
	$(MAKE) -C src/algobjs

crypter:
	$(MAKE) -C src/crypters

clean:
	rm -f libcryptolib.a
	$(MAKE) -C src/algobjs clean
	$(MAKE) -C src/crypters clean

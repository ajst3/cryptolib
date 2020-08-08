
.DEFAULT_GOAL := all

all: algorithms crypter

algorithms:
	$(MAKE) -C src/algobjs

crypter:
	$(MAKE) -C src/crypters

#ifndef DECRYPTER
#define DECRYPTER
#include "cryptobase.hpp"
class decrypter {
private:
  char *fullciphertext;
  int blocknum;
  int textlen;
  int numblocks;
  char *plaintext;

  char *nextBlock();
  static char *getBlock(long block, char *fullciphertext);
  void cbcmode(cryptobase *algorithm, char *iv);
  void cbcparallel(cryptobase *algorithm, char *iv);
  static void *cbcparrblock(void *args);

public:
  decrypter(char *fct);
  char *decrypt(cryptobase *algorithm, int blockmode, char *iv);
  ~decrypter(void);
};

#endif

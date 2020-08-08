#ifndef BLOWFISH
#define BLOWFISH
#include "cryptobase.hpp"

#define PARRSIZE 18
#define KEYSIZE 256
#define PARRSIZE 18
class blowfish : public cryptobase {
private:
  int *key;
  unsigned int parr[PARRSIZE];

  void initPArray();
  char *round(int rnum, char *plaintextpart1, char *plaintextpart2,
              int decrypting);
  char *fblock(char *finput);
  char *encryptblockp(char *p1, char *p2);
  char *decryptblockp(char *p1, char *p2);

public:
  blowfish(int *k);
  char *encryptBlock(char *block);
  char *decryptBlock(char *block);
  ~blowfish(void);

  // Test Functions
  void initPArrayTest();
  void roundTest(char *block);
  void encryptblockTest(char *block);
  void decryptblockTest(char *todecrypt);
};

#endif

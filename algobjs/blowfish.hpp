#include "textmanager.hpp"
#define PARRSIZE 18
class blowfish: public cryptobase {
private:
  int *key;
  unsigned int parr[PARRSIZE];
  char *ptext;
  textmanager ptextman;

  void initPArray();
  char *round(int rnum, char *plaintextpart1, char *plaintextpart2,
              int decrypting);
  char *fblock(char *finput);
  char *encryptblockp(char *p1, char *p2);
  char *decryptblockp(char *p1, char *p2);

public:
  blowfish(int *k, char *text);
  char *encryptBlock();
  char *decryptBlock();
  void nextBlock(char *nextBlock);
  ~blowfish(void);

  // Test Functions
  void initPArrayTest();
  void roundTest();
  void encryptblockTest();
  void decryptblockTest(char *todecrypt);
};

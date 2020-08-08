#include "cryptobase.hpp"
class encrypter {
private:
  char *fulltext;
  int blocknum;
  int textlen;
  char *ciphertext;

  char *nextBlock();
  char *encryptBlock();

public:
  encrypter(char *ft);
  char *encrypt(cryptobase *algorithm, int blockmode, char *iv);
  ~encrypter(void);
};

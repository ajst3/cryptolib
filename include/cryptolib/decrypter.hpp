#include "cryptobase.hpp"
class decrypter {
private:
  char *fullciphertext;
  int blocknum;
  int textlen;
  char *plaintext;

  char *nextBlock();
  char *decryptBlock();

public:
  decrypter(char *fct);
  char *decrypt(cryptobase *algorithm, int blockmode, char *iv);
  ~decrypter(void);
};

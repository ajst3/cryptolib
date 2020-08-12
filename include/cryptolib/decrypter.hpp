#ifndef DECRYPTER
#define DECRYPTER
#include "cryptobase.hpp"

//! Class used to decrypt a string using a blockmode

//! \headerfile cryptolib/decrypter.hpp <cryptolib/decrypter.hpp>
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
  //! Initializes object with full ciphertext
  decrypter(char *fct);

  //! Decrypts the string passed into the constructor
  /*!
    algorithm is an object that implements cryptobase to decrypt a block.
    blockmode is the blockmode listed in the enum.
    iv is a char array that represents the iv used when encrypting.
  */
  char *decrypt(cryptobase *algorithm, int blockmode, char *iv);

  //! Destroys object
  ~decrypter(void);
};

#endif

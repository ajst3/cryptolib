#ifndef ENCRYPTER
#define ENCRYPTER

#include "cryptobase.hpp"

//! Class used to encrypt a string using a blockmode

//! \headerfile cryptolib/encrypter.hpp <cryptolib/encrypter.hpp>
class encrypter {
private:
  char *fulltext;
  int blocknum;
  int textlen;
  char *ciphertext;

  char *nextBlock();
  void cbcmode(cryptobase *algorithm, char *iv);

public:
  //! Initializes object with full plaintext
  encrypter(char *ft);

  //! Encrypts the string passed into the constuctor
  /*!
    algorithm is an object that implements cryptobase to encrypt a block.
    blockmode is the blockmode listed in the enum.
    iv is a char array that represents the iv.
  */
  char *encrypt(cryptobase *algorithm, int blockmode, char *iv);

  //! Destroys object
  ~encrypter(void);
};

#endif

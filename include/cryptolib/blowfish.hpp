#ifndef BLOWFISH
#define BLOWFISH
#include "cryptobase.hpp"

#define PARRSIZE 18
#define KEYSIZE 256
#define PARRSIZE 18

//! Class used for encrypting and decrypting using Blowfish algorithm

//! \headerfile cryptolib/blowfish.hpp <cryptolib/blowfish.hpp>
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
  //! Initializes object with key
  /*!
    int *k is a pointer to an array of ints representing
    the key.
  */
  blowfish(int *k);

  //! Destroys object
  ~blowfish(void);

  //! Encrypts block
  /*!
    Encrypt the string block and return the encrypted value
    in a char array.
  */
  char *encryptBlock(char *block);

  //! Decrypts block
  /*!
    Decrypt the string, block, and return the decrypted value
    in a char array.
  */
  char *decryptBlock(char *block);

  //! Unit test functions
  void initPArrayTest();
  void roundTest(char *block);
  void encryptblockTest(char *block);
  void decryptblockTest(char *todecrypt);
};

#endif

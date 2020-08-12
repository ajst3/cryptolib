#ifndef CRYPTOBASE
#define CRYPTOBASE

//! Baseclass for cryptographic algorithms

//! \headerfile cryptolib/cryptobase.hpp <cryptolib/cryptobase.hpp>
class cryptobase {
public:
  virtual char *encryptBlock(char *block) = 0;
  virtual char *decryptBlock(char *block) = 0;
};

#endif

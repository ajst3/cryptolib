/*
* Base class used to define an interface for the crypto
* algorithm objects. Also used for the generic in encrypter/decrypter.
*/

#ifndef CRYPTOBASE
#define CRYPTOBASE

class cryptobase {
public:
  virtual char *encryptBlock(char *block) = 0;
  virtual char *decryptBlock(char *block) = 0;
};

#endif

/*
* Base class used to define an interface for the crypto
* algorithm objects. Also used for the generic in encrypter/decrypter.
*/

class cryptobase {
public:
  virtual void nextBlock() = 0;
  virtual char *encryptBlock() = 0;
  virtual char *decryptBlock() = 0;
}

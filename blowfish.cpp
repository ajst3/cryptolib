/*
* Functions that implement blowfish algorithm.
*/
#include <stdlib.h>
#include "constants.h"

#define KEYSIZE 256
#define PARRSIZE 18

using namespace std;

class blowfish {
private:
  int *key;
  unsigned int parr[PARRSIZE];
  char *ptext

  /*
  * Initializing parray with input key
  */
  void initPArray()
  {
    int i;
    for(i = 0; i < PARRSIZE; i+=4)
    {
      parr[i+3] = parray[i-4] ^ key[(i+3) % (KEYSIZE/8)]; // 3
      parr[i+2] = parray[i-4] ^ key[(i+2) % (KEYSIZE/8)]; // 2
      parr[i+1] = parray[i-4] ^ key[(i+1) % (KEYSIZE/8)]; // 1
      parr[i] = parray[i-4] ^ key[(i) % (KEYSIZE/8)]; // 0
    }
  }

public:
  // Constructor
  blowfish(int *k, char *plaintext)
  {
    key = k;
    parr = malloc(sizeof(unsigned long) * PARRSIZE);
    ptext = plaintext;
  }

  // Deconstructor
  virtual ~name_t();
};

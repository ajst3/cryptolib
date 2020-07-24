/*
* Functions that implement blowfish algorithm.
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"

#define KEYSIZE 256
#define PARRSIZE 18

using namespace std;

class blowfish {
private:
  int *key;
  unsigned int parr[PARRSIZE];
  char *ptext;

  void initPArray();

public:
  // Constructor
  blowfish(int *k, char *plaintext);

  void initPArrayTest();

  // Deconstructor
  ~blowfish(void);
};

blowfish::blowfish(int *k, char *plaintext)
{
  key = k;
  ptext = plaintext;
}

blowfish::~blowfish()
{

}

/*
* Initializing parray with input key
*/
void blowfish::initPArray()
{
  int i;
  for(i = 0; i < PARRSIZE; ++i)
  {
    parr[i] = parray[i] ^ key[(i) % (KEYSIZE/32)]; // 0
  }
}

void blowfish::initPArrayTest()
{
  printf("before = %d\n", parray[7]);
  initPArray();
  printf("after = %d\n", parr[7]);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int key[KEYSIZE/32];
  int i;
  for(i = 0; i < KEYSIZE/32; ++i)
  {
    key[i] = rand();
  }
  char test[] = "hello";
  blowfish bfishtest = blowfish(key, test);
  printf("made blowfish obj\n");
  bfishtest.initPArrayTest();
  return 0;
}

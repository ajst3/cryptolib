#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "algobjs/blowfish.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  //srand(100);
  int key[KEYSIZE/32];
  int i;
  for(i = 0; i < KEYSIZE/32; ++i)
  {
    key[i] = rand();
  }
  char test[] = "hellowo";
  blowfish bfishtest = blowfish(key, test);
  printf("made blowfish obj\n");
  bfishtest.initPArrayTest();
  bfishtest.roundTest();
  bfishtest.encryptblockTest();
  return 0;
}

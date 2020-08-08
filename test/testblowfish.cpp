#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cryptolib/blowfish.hpp>

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int key[KEYSIZE/32];
  int i;
  for(i = 0; i < KEYSIZE/32; ++i)
  {
    key[i] = rand();
  }
  char test[] = "axtkgh7";
  printf("encrypting %s\n", test);
  blowfish bfishtest = blowfish(key);
  char *encres = bfishtest.encryptBlock(test);
  printf("encres = %s\n", encres);
  char *decres = bfishtest.decryptBlock(encres);
  printf("decres = %s\n", decres);
  return 0;
}

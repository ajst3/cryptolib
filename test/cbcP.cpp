#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cryptolib/blowfish.hpp>
#include <cryptolib/encrypter.hpp>
#include <cryptolib/decrypter.hpp>
#include <cryptolib/blockmodes.hpp>

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int key[KEYSIZE/32];
  int i;
  for(i = 0; i < KEYSIZE/32; ++i)
  {
    key[i] = rand();
  }
  char test[] = "0123456776543210";
  printf("encrypting %s\n", test);
  blowfish bfish = blowfish(key);
  encrypter enc = encrypter(test);
  char iv[] = "ghflsjo8";
  char * ciphertext = enc.encrypt(&bfish, CBC_PARALLEL, iv);
  printf("encres = %s\n", ciphertext);
  decrypter dec = decrypter(ciphertext);
  char *decres = dec.decrypt(&bfish, CBC_PARALLEL, iv);
  printf("decres = %s\n", decres);
  return 0;
}

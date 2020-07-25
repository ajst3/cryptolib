/*
* Class that implement blowfish algorithm.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"
#include "textmanager.hpp"
#include "blowfish.hpp"

#define KEYSIZE 256
#define PARRSIZE 18
#define MAXINTB 4294967296

using namespace std;

blowfish::blowfish(int *k, char *plaintext)
  : ptextman (plaintext)
{
  key = k;
  ptext = plaintext;
  ptextman = textmanager(ptext);
}

blowfish::~blowfish()
{

}

/*
* Initializing parray with input key.
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

char* blowfish::round(int rnum, char *plaintextpart1, char *plaintextpart2)
{
  // xor the pval with the first 32bits of the block
  char *right = xorwithpval(parr[rnum], plaintextpart1);
  char *left = xortwochararray(fblock(right), plaintextpart2);
  char *rblock = (char *) malloc(sizeof(char) * 8);
  strcat(rblock, left);
  strcat(rblock, right);
  free(left);
  free(right);
  return rblock;
}

char* blowfish::fblock(char *finput)
{
  unsigned int s1res = (unsigned char) finput[0];
  unsigned int s2res = (unsigned char) finput[1];
  unsigned int s3res = (unsigned char) finput[2];
  unsigned int s4res = (unsigned char) finput[3];

  long temp = s1res + s2res;
  unsigned int s12inter = temp % MAXINTB;
  unsigned int s123inter = s12inter ^ s3res;
  temp = s123inter + s4res;
  unsigned int result = temp % MAXINTB;

  return tochararray(result);
}

void blowfish::roundTest()
{
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  printf("first block = %s\n", blockpart1);
  printf("second block = %s\n", blockpart2);
  char *res = round(0, blockpart1, blockpart2);
  printf("res - %s\n", res);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int key[KEYSIZE/32];
  int i;
  for(i = 0; i < KEYSIZE/32; ++i)
  {
    key[i] = rand();
  }
  char test[] = "1234567";
  blowfish bfishtest = blowfish(key, test);
  printf("made blowfish obj\n");
  bfishtest.initPArrayTest();
  bfishtest.roundTest();
  return 0;
}

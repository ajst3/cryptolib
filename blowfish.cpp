/*
* Class that implement blowfish algorithm.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"
#include "blowfish.hpp"

#define KEYSIZE 256
#define PARRSIZE 18
#define MAXINTB (unsigned int) 1 << 31
//429496729

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
    parr[i] = parray[i] ^ key[(i) % (KEYSIZE/32)];
  }
}

char* blowfish::round(int rnum, char *plaintextpart1, char *plaintextpart2,
                      int decrypting)
{
  // xor the pval with the first 32bits of the block
  char *right;
  if(decrypting != 0)
  {
    right = xorwithpval(parr[rnum], plaintextpart1);
  }
  else
  {
    right = xorwithpval(parr[17 - rnum], plaintextpart1);
  }
  char *left = xortwochararray(fblock(right), plaintextpart2);
  char *rblock = (char *) malloc(sizeof(char) * 8);
  copytoarray(rblock, left, right);
  free(left);
  free(right);
  return rblock;
}

char* blowfish::fblock(char *finput)
{
  unsigned int s1res = sbox0[(unsigned char) finput[0]];
  unsigned int s2res = sbox1[(unsigned char) finput[1]];
  unsigned int s3res = sbox2[(unsigned char) finput[2]];
  unsigned int s4res = sbox3[(unsigned char) finput[3]];

  unsigned long temp = s1res + s2res;
  //unsigned int s12inter = (s1res + s2res) % MAXINTB;
  unsigned int s12inter = temp % MAXINTB;
  unsigned int s123inter = s12inter ^ s3res;
  temp = s123inter + s4res;
  //unsigned int result = (s123inter + s4res) % MAXINTB;
  unsigned int result = temp % MAXINTB;

  return tochararray(result);
}

char* blowfish::encryptblock(char *p1, char *p2)
{
  char *inter;
  char *p1inter = (char *) malloc(sizeof(char) * 4);
  char *p2inter = (char *) malloc(sizeof(char) * 4);
  char *encblock = (char *) malloc(sizeof(char) * 8);
  int i;
  for(i = 0; i < 16; ++i)
  {
    if(i == 0)
    {
      inter = round(i, p1, p2, 1);
    }
    else
    {
      inter = round(i, p1inter, p2inter, 1);
    }
    splitblock(inter, p1inter, p2inter);
    if(i == 0 || i == 3)
    {
      printf("inter test = %s,   %s,    %s\n", p1inter, p2inter, inter);
    }
    free(inter);
  }

  p1inter = xorwithpval(parray[16], p1inter);
  p2inter = xorwithpval(parray[17], p2inter);

  copytoarray(encblock, p2inter, p1inter);
  free(p2inter);
  free(p1inter);
  return encblock;
}

char* blowfish::decryptblock(char *p1, char *p2)
{
  char *inter;
  char *p1inter = (char *) malloc(sizeof(char) * 4);
  char *p2inter = (char *) malloc(sizeof(char) * 4);
  char *decblock = (char *) malloc(sizeof(char) * 8);
  int i;
  for(i = 0; i < 16; ++i)
  {
    if(i == 0)
    {
      inter = round(i, p1, p2, 0);
    }
    else
    {
      inter = round(i, p1inter, p2inter, 0);
    }
    splitblock(inter, p1inter, p2inter);
    if(i == 0)
    {
      printf("inter test = %s,   %s,    %s\n", p1inter, p2inter, inter);
    }
    free(inter);
  }

  p1inter = xorwithpval(parray[1], p1inter);
  p2inter = xorwithpval(parray[0], p2inter);

  copytoarray(decblock, p2inter, p1inter);
  free(p2inter);
  free(p1inter);
  return decblock;
}


void blowfish::initPArrayTest()
{
  printf("before = %d\n", parray[7]);
  initPArray();
  printf("after = %d\n", parr[7]);
}

void blowfish::roundTest()
{
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  printf("first block = %s\n", blockpart1);
  printf("second block = %s\n", blockpart2);
  char *res = round(0, blockpart1, blockpart2, 1);
  printf("res - %s\n", res);
  free(blockpart1);
  free(blockpart2);
  free(res);
}

void blowfish::encryptblockTest()
{
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  printf("first block = %s\n", blockpart1);
  printf("second block = %s\n", blockpart2);
  char *encres = encryptblock(blockpart1, blockpart2);
  printf("encres = %s\n", encres);
  free(blockpart1);
  free(blockpart2);
  decryptblockTest(encres);
}

void blowfish::decryptblockTest(char *todecrypt)
{
  char *b1 = (char *) malloc(sizeof(char) * 4);
  char *b2 = (char *) malloc(sizeof(char) * 4);
  splitblock(todecrypt, b1, b2);
  char *decres = decryptblock(b1, b2);
  printf("after decrypt = %s\n", decres);
}

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

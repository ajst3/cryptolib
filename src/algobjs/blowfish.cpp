/*
* Class that implement blowfish algorithm.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "blowfishconstants.h"
#include "textmanager.hpp"
#include <cryptolib/blowfish.hpp>

#define MAXINTB (unsigned int) 1 << 31

using namespace std;

blowfish::blowfish(int *k)
{
  key = k;
  initPArray();
}

blowfish::~blowfish()
{

}

/*
* Initializing parray with input key. Loops through all
* elements of the parray xoring it with the corresponding
* part of the key. If the key size is smaller than 18 bytes,
* we loop around to the start and continue.
*/
void blowfish::initPArray()
{
  int i;
  for(i = 0; i < PARRSIZE; ++i)
  {
    parr[i] = parray[i] ^ key[(i) % (KEYSIZE/32)];
  }
}

/*
* Does one round on the plaintext or ciphertext blocks given.
* decyrpting is a flag to determine what element in the parray we
* use. This function implements the standard blowfish round.
*/
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

/*
* Given a char array of 4 bytes, we use that to get the output
* of the standard blowfish f block.
*/
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

/*
* Implements the encryption of a singular block.
* Given two parts of a block performs 16 rounds on them
* and does the postprocessing. Returns a pointer to the
* encrypted block.
*/
char* blowfish::encryptblockp(char *p1, char *p2)
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

/*
* Decrypts a singular block. Given two parts of a block,
* perform 16 rounds and does the postprocessing. Returns
* a pointer to the decrypted block.
*/
char* blowfish::decryptblockp(char *p1, char *p2)
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

char* blowfish::encryptBlock(char *block)
{
  textmanager ptextman = textmanager(block);
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  return encryptblockp(blockpart1, blockpart2);
}

char* blowfish::decryptBlock(char *block)
{
  textmanager ptextman = textmanager(block);
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  return decryptblockp(blockpart1, blockpart2);
}

/*
* Tester functions.
*/

void blowfish::initPArrayTest()
{
  printf("before = %d\n", parray[7]);
  initPArray();
  printf("after = %d\n", parr[7]);
}

void blowfish::roundTest(char *block)
{
  textmanager ptextman = textmanager(block);
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

void blowfish::encryptblockTest(char *block)
{
  textmanager ptextman = textmanager(block);
  char *blockpart1 = ptextman.substring(0);
  char *blockpart2 = ptextman.substring(4);
  printf("first block = %s\n", blockpart1);
  printf("second block = %s\n", blockpart2);
  char *encres = encryptblockp(blockpart1, blockpart2);
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
  char *decres = decryptblockp(b1, b2);
  printf("after decrypt = %s\n", decres);
}

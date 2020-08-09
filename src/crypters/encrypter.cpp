/*
* Class used to encrypt multiple blocks using
* a given string
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../textmanager.hpp"
#include <cryptolib/encrypter.hpp>
#include <cryptolib/blockmodes.hpp>

#define BLOCKSIZE 8

using namespace std;

encrypter::encrypter(char *ft)
{
  fulltext = ft;
  blocknum = 0;
  textlen = strlen(ft);
  ciphertext = (char *) malloc(sizeof(char) * textlen);
}

encrypter::~encrypter(void)
{

}

char* encrypter::nextBlock()
{
  char *next = (char *) malloc(sizeof(char) * BLOCKSIZE);
  int i;
  int s = 0;
  int start = blocknum * BLOCKSIZE;
  for(i = blocknum * BLOCKSIZE; i < BLOCKSIZE + start; ++i)
  {
    if(i > textlen)
    {
      free(next);
      return NULL;
    }
    next[s++] = fulltext[i];
  }
  ++blocknum;
  return next;
}

void encrypter::cbcmode(cryptobase *algorithm, char *iv)
{
  char *prev = iv;

  while(true)
  {
    char *next = nextBlock();
    if(next == NULL)
    {
      break;
    }

    char *toencrypt = xortwochararray(next, prev, BLOCKSIZE);
    if(prev != iv)
    {
      free(prev);
    }

    prev = algorithm->encryptBlock(toencrypt);
    appendtochararray(ciphertext, prev, blocknum - 1, BLOCKSIZE);
    free(toencrypt);
    free(next);
  }
}

char* encrypter::encrypt(cryptobase *algorithm, int blockmode, char *iv)
{
  if(blockmode == CBC or blockmode == CBC_PARALLEL)
  {
    cbcmode(algorithm, iv);
  }
  return ciphertext;
}

/*
* Class used to encrypt multiple blocks using
* a given string
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "textmanager.hpp"
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
    next[s++] = fulltext[i];
    if(i > textlen)
    {
      free(next);
      return NULL;
    }
  }
  ++blocknum;
  return next;
}

char* encrypter::encrypt(cryptobase *algorithm, int blockmode, char *iv)
{
  // for now only one block mode (CBC)
  char *prev = iv;

  while(true)
  {
    char *next = nextBlock();
    if(next == NULL)
    {
      break;
    }

    char *toencrypt = xortwochararray(next, prev);
    free(next);
    if(prev != iv) // check to make sure prev is not pointing to the stack
    {
      free(prev);
    }

    prev = algorithm->encryptBlock(toencrypt);
    appendtochararray(ciphertext, prev, blocknum - 1, BLOCKSIZE);
    free(toencrypt);
  }
  return ciphertext;
}

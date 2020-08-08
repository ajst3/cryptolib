/*
* Class used to decrypt multiple blocks using
* a given string
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "textmanager.hpp"
#include <cryptolib/decrypter.hpp>
#include <cryptolib/blockmodes.hpp>

#define BLOCKSIZE 8

using namespace std;

decrypter::decrypter(char *fct)
{
  fullciphertext = fct;
  blocknum = 0;
  textlen = strlen(fct);
  plaintext = (char *) malloc(sizeof(char) * textlen);
}

decrypter::~decrypter(void)
{

}

char* decrypter::nextBlock()
{
  char *next = (char *) malloc(sizeof(char) * BLOCKSIZE);
  int i;
  int s = 0;
  int start = blocknum * BLOCKSIZE;
  for(i = blocknum * BLOCKSIZE; i < BLOCKSIZE + start; ++i)
  {
    next[s++] = fullciphertext[i];
    if(i > textlen)
    {
      free(next);
      return NULL;
    }
  }
  ++blocknum;
  return next;
}

char* decrypter::decrypt(cryptobase *algorithm, int blockmode, char *iv)
{
  char *prev = iv;

  while(true)
  {
    char *next = nextBlock();
    if(next == NULL)
    {
      break;
    }

    char *toxor = algorithm->decryptBlock(next);
    char *toappend = xortwochararray(toxor, prev);

    if(prev != iv) // check to make sure prev is not pointing to the stack
    {
      free(prev);
    }
    prev = next;

    appendtochararray(plaintext, toappend, blocknum - 1, BLOCKSIZE);
    free(toappend);
    free(toxor);
  }
  return plaintext;
}
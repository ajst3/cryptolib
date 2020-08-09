/*
* Class used to decrypt multiple blocks using
* a given string
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "../textmanager.hpp"
#include <cryptolib/decrypter.hpp>
#include <cryptolib/blockmodes.hpp>

#define BLOCKSIZE 8
#define NUM_THREADS 4

using namespace std;

struct pblock
{
  char *text;
};

struct threadargs
{
  long threadRank;
  cryptobase *algorithm;
  struct pblock *pblocks;
  int numb;
  char *ciphertext;
};

decrypter::decrypter(char *fct)
{
  fullciphertext = fct;
  blocknum = 0;
  textlen = strlen(fct);
  numblocks = textlen / BLOCKSIZE;
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
    if(i > textlen)
    {
      free(next);
      return NULL;
    }
    next[s++] = fullciphertext[i];
  }
  ++blocknum;
  return next;
}

char* decrypter::getBlock(long block, char *fullciphertext)
{
  char *next = (char *) malloc(sizeof(char) * BLOCKSIZE);
  int i;
  int s = 0;
  int start = block * BLOCKSIZE;
  for(i = block * BLOCKSIZE; i < BLOCKSIZE + start; ++i)
  {
    next[s++] = fullciphertext[i];
  }
  return next;
}

void decrypter::cbcmode(cryptobase *algorithm, char *iv)
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
    char *toappend = xortwochararray(toxor, prev, BLOCKSIZE);
    if(prev != iv)
    {
      free(prev);
    }

    prev = next;

    appendtochararray(plaintext, toappend, blocknum - 1, BLOCKSIZE);
    free(toappend);
    free(toxor);
  }
}

void* decrypter::cbcparrblock(void *args)
{
  struct threadargs *input = (struct threadargs *) args;
  const long rank = input->threadRank;
  cryptobase *algorithm = input->algorithm;
  struct pblock *blocks = input->pblocks;
  int numblocks = input->numb;
  char *fullciphertext = input->ciphertext;

  const int local = numblocks / NUM_THREADS;
  const int first = rank * local;
  int last = ((rank+1) * local) - 1;

  if(numblocks % NUM_THREADS != 0 &&
     rank == NUM_THREADS - 1)
  {
    last += numblocks % NUM_THREADS;
  }

  int i;
  for(i = first; i <= last; ++i)
  {
    char *toadd = algorithm->decryptBlock(getBlock(rank, fullciphertext));
    struct pblock *newb = (struct pblock *) malloc(sizeof(struct pblock));
    newb->text = toadd;
    blocks[i] = *newb;
  }
  return NULL;
}

void decrypter::cbcparallel(cryptobase *algorithm, char *iv)
{
  struct pblock *decryptedBlocks =
    (struct pblock *) malloc(sizeof(struct pblock) * numblocks);
  pthread_t *threadHandles = (pthread_t *)
    malloc(NUM_THREADS * sizeof(pthread_t));
  long thread;
  for(thread = 0; thread < NUM_THREADS; ++thread)
  {
    struct threadargs input;
    input.threadRank = thread;
    input.algorithm = algorithm;
    input.pblocks  = decryptedBlocks;
    input.numb = numblocks;
    input.ciphertext = fullciphertext;
    pthread_create(&threadHandles[thread], NULL,
      cbcparrblock, (void*)&input);
  }

  for(thread = 0; thread < NUM_THREADS; ++thread)
  {
    pthread_join(threadHandles[thread], NULL);
  }

  int i;
  for(i = 0; i < numblocks; ++i)
  {
    appendtochararray(plaintext, decryptedBlocks[i].text, i, BLOCKSIZE);
  }
}

char* decrypter::decrypt(cryptobase *algorithm, int blockmode, char *iv)
{
  if(blockmode == CBC)
  {
    cbcmode(algorithm, iv);
  }
  else if(blockmode == CBC_PARALLEL)
  {
    cbcparallel(algorithm, iv);
  }

  plaintext[((blocknum + 1) * BLOCKSIZE) - 1] = '\0';
  return plaintext;
}

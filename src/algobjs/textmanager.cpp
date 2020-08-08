/*
* Class that manages the plaintext for the crypto algorithm.
*/
#include <stdlib.h>
#include <stdio.h>
#include "../textmanager.hpp"

using namespace std;

textmanager::textmanager(char *text)
{
  txt = text;
}

textmanager::~textmanager(void)
{

}

/*
* Returns two 32 bit halves of the next 64 bits from the string.
*/
char* textmanager::substring(int begin)
{
  char *sub = (char *) malloc(sizeof(char) * 4);
  int end = begin + 4;
  int i;
  int s = 0;
  for(i = begin; i < end; ++i)
  {
    sub[s++] = txt[i];
  }
  return sub;
}

/*
* Returns char array after performing xor with pval.
* Does this by converting pval a char array and passing
* into function for two char arrays.
*/
char *xorwithpval(unsigned int pval, char *part)
{
  char *pchar = tochararray(pval);
  return xortwochararray(pchar, part, 4);
}

/*
* Returns a pointer to the char array containing
* the result of xoring the two given char arrays.
*/
char *xortwochararray(char *x, char *y, int arrsize)
{
  char *afterxor = (char *) malloc(sizeof(char) * arrsize);
  int i;
  for(i = 0; i < arrsize; ++i)
  {
    afterxor[i] = x[i] ^ y[i];
  }
  return afterxor;
}

/*
* Converts an integer to a char array for the purposes
* of making operations between char arrays and ints easier.
* Returns a pointer to the resultsing char array.
*/
char *tochararray(unsigned int input)
{
  char *result = (char *) malloc(sizeof(char) * 4);
  int i;
  for(i = 0; i < 4; ++i)
  {
    result[i] = (input >> (i * 8)) & 0xFF;
  }
  return result;
}

/*
* Because we are dealing with blocks (parts of strings),
* we cannot trust strcpy/strncpy to combine our blocks.
* This function copies the bytes in p1 and p2 into
* a new char array and returns it.
* NOTE: p1 is copies and then p2 is appended.
*/
void copytoarray(char *dest, char *p1, char *p2)
{
  int i;
  int s = 0;
  for(i = 0; i < 8; ++i)
  {
    if(i < 4)
    {
      dest[i] = p1[i];
    }
    else
    {
      dest[i] = p2[s++];
    }
  }
}

/*
* Splits the given block into two parts.
* The first half is copied into p1 and the
* second half is copied into p2.
*/
void splitblock(char *block, char *p1, char *p2)
{
  int i;
  int s = 0;
  for(i = 0; i < 8; ++i)
  {
    if(i < 4)
    {
      p1[i] = block[i];
    }
    else
    {
      p2[s++] = block[i];
    }
  }
}

void appendtochararray(char *text, char *toappend, int blocknum, int blocksize)
{
  int i;
  int start = blocknum * blocksize;
  int s = 0;
  for(i = start; i < start + blocksize; ++i)
  {
    text[i] = toappend[s++];
  }
}

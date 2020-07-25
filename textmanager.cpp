/*
* Class that manages the plaintext for the crypto algorithm.
*/
#include <stdlib.h>
#include "textmanager.hpp"

using namespace std;

textmanager::textmanager(char *text)
{
  txt = text;
}

textmanager::~textmanager(void)
{

}

/*
* Returns two 32 bit halves of the next 64 bits from the string
*/
char* textmanager::substring(int begin)
{
  char *sub = (char *) malloc(sizeof(char) * 4);
  int end = begin + 4;
  int i;
  for(i = begin; i < end; ++i)
  {
    sub[i] = txt[i];
  }
  return sub;
}

/*
* Returns char array after performing xor with pval
*/
char *xorwithpval(unsigned int pval, char *part)
{
  char *afterxor = (char *) malloc(sizeof(char) * 4);
  int i;
  for(i = 0; i < 4; ++i)
  {
    afterxor[i] = part[i] ^ (pval >> (i * 8));
  }
  return afterxor;
}

char *xortwochararray(char *x, char *y)
{
  char *afterxor = (char *) malloc(sizeof(char) * 4);
  int i;
  for(i = 0; i < 4; ++i)
  {
    afterxor[i] = x[i] ^ y[i];
  }
  return afterxor;
}

char *tochararray(unsigned int input)
{
  char *result = (char *) malloc(sizeof(char) * 4);
  int i;
  for(i = 0; i < 4; ++i)
  {
    result[i] = (input >> (i * 8)) & 0xff;
  }
  return result;
}

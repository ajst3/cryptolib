class blowfish {
private:
  int *key;
  unsigned int parr[PARRSIZE];
  char *ptext;
  textmanager ptextman;

  void initPArray();
  char *round(int rnum, char *plaintextpart1, char *plaintextpart2);
  char *fblock(char *finput);

public:
  blowfish(int *k, char *plaintext);
  void initPArrayTest();
  void roundTest();
  ~blowfish(void);
};

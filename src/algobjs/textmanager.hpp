class textmanager {
private:
  char *txt;

public:
  textmanager(char *text);
  char *substring(int begin);
  ~textmanager(void);

};

char *xorwithpval(unsigned int pval, char *part);
char *tochararray(unsigned int input);
char *xortwochararray(char *x, char *y);
void copytoarray(char *dest, char *p1, char *p2);
void splitblock(char *block, char *p1, char *p2);
void appendtochararray(char *text, char *toappend, int blocknum, int blocksize);

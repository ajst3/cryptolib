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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char str[51] = {'\0'};
  int pos;
  long int b;

  if (scanf("%s", str) == -1) exit(1);
  if (scanf("%ld", &b) == -1) exit(1);

  pos = b%strlen(str);
  if (pos == 0) pos = strlen(str);
  printf("%c\n", str[pos-1]);

  return 0;
}


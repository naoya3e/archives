#include <stdio.h>
#include <string.h>

int main() {
  char str[120] = {'\0'};

  scanf("%s", str);

  str[strlen(str)-1] = '5';
  printf("%s\n", str);

  return 0;
}


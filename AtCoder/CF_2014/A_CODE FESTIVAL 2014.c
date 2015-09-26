#include <stdio.h>
#include <string.h>

int main() {
  char str[30] = {'\0'};

  scanf("%s", str);
  strcat(str, "2014");
  printf("%s\n", str);

  return 0;
}


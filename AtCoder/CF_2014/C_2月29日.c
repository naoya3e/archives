#include <stdio.h>

int main() {
  int last = 0;
  int sleap, eleap;
  long int start, end;

  scanf("%ld", &start);
  scanf("%ld", &end);

  if (start%4 == 0 && start%100 != 0 || start%400 == 0) last = 1;

  sleap = start/4-start/100+start/400;
  eleap = end/4-end/100+end/400;

  printf("%d\n", eleap-sleap+last);

  return 0;
}


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int i = 1;
  int a, N;
  int sum = 0;

  scanf("%d", &N);
  while (scanf("%d", &a) != EOF) {
    sum += a * pow(2, N-i);
    i++;
  }

  printf("%d\n", sum);

  return 0;
}


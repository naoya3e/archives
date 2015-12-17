#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double getRand(double min, double max) {
  return min + (double)(rand() * (max-min+1.0)/(1.0+RAND_MAX));
}

int main() {
  int i, n;

  printf("0以上100以下のn個のランダムな実数を生成します : ");
  scanf("%d", &n);

  srand((unsigned int)time(NULL));

  for (i=0; i<n; i++) {
    printf("%f ", getRand(0, 100));
  }
  printf("\n");

  return 0;
}


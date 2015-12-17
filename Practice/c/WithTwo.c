#include <stdio.h>

int withTwo(int n) {
  int q, r;

  q = n/10;
  r = n%10;

  if (r == 2) {
    return 1;
  } else if (q == 0) {
    return 0;
  } else {
    withTwo(q);
  }
}

int main(void) {
  int n;

  printf("入力した数値が 2 を含むかどうかを判定します：");
  scanf("%d", &n);

  if (withTwo(n) == 1) {
    printf("%d は 2 を含んでいます\n", n);
  } else {
    printf("%d は 2 を含んでいません\n", n);
  }

  return 0;
}


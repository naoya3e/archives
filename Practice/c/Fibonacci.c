#include <stdio.h>

int fib(int n) {
  switch(n) {
    case  0: return 0;
    case  1: return 1;
    default: return fib(n-1) + fib(n-2);
  }
}

int main(void) {
  int n;

  printf("fib(n)を求めます：");
  scanf("%d", &n);

  printf("fib(%d) = %d\n", n, fib(n));

  return 0;
}


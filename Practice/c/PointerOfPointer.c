#include <stdio.h>
#include <stdlib.h>

int main() {
  int number = 1024;
  int  *x;
  int **y;

  char message[256] = "Hello, world!";
  char  *p;
  char **q;

  // 初期状態
  x = &number;
  y = &x;

  printf(" *x: %d\n",  *x);
  printf("**y: %d\n", **y);

  // 書き換える
  **y = 2048;

  printf(" *x: %d\n",  *x);
  printf("**y: %d\n", **y);

  printf("\n");

  // 初期状態
  p = message;
  q = &p;

  printf("  p: %s\n",  p);
  printf(" *q: %s\n", *q);

  // 書き換える
  *q = "Hello, Clang!";

  printf("  p: %s\n",  p);
  printf(" *q: %s\n", *q);

  return 0;
}


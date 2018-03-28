#include <stdio.h>

int main() {
  int year;

  printf("西暦を入力してください: ");
  scanf("%d", &year);

  if (year%4 == 0 && year%100 != 0 || year%400 == 0) {
    printf("%d年は閏年です\n", year);
  } else {
    printf("%d年は閏年ではありません\n", year);
  }

  return 0;
}

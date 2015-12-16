#include <stdio.h>

int int_power(int p, int power);
int power_sum(int numbers[], int n, int power);

int main(void) {
  int i;
  int numbers[100], n;
  int power;
  int sum;

  printf("いくつかの整数とべき乗値を入力し、入力した整数のべき乗和を求めます\n");

  printf("入力する整数を入力してください：");
  scanf("%d", &n);

  for (i=0; i<n; i++) {
    printf("%d番目のデータを入力してください：", i+1);
    scanf("%d", &numbers[i]);
  }

  printf("べき乗値を入力してください：");
  scanf("%d", &power);

  sum = power_sum(numbers, n, power);

  printf("求める和は %d です\n", sum);

  return 0;
}

int int_power(int p, int power) {
  int i;
  int value = 1;

  for (i=0; i<power; i++) {
    value *= p;
  }

  return value;
}

int power_sum(int numbers[], int n, int power) {
  int i;
  int p;
  int sum = 0;

  for (i=0; i<n; i++) {
    p = numbers[i];
    sum += int_power(p, power);
  }

  return sum;
}


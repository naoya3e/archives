#include <stdio.h>

int main() {
  int m;

  scanf("%d", &m);

  if (m < 100) {
    printf("%02d", 0);
  } else if (100 <= m && m <= 5000) {
    printf("%02d", m/100);
  } else if (6000 <= m && m <= 30000) {
    printf("%02d", m/1000 + 50);
  } else if (35000 <= m && m <= 70000) {
    printf("%02d", (m/1000 -30) / 5 + 80);
  } else if (70000 < m) {
    printf("%02d", 89);
  }
  printf("\n");

  return 0;
}


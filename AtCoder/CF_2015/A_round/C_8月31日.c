#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
  return *(int *)b - *(int *)a;
}

int main() {
  int i;
  int n, t;
  int a, b;
  int dis[100000];
  int sum = 0;

  scanf("%d %d", &n, &t);
  for (i=0; i<n; i++) {
    scanf("%d %d", &a, &b);
    sum += a;
    dis[i] = a-b;
  }

  qsort(dis, n, sizeof(int), &compare);

  for (i=0; i<n; i++) {
    if (sum <= t) break;
    sum -= dis[i];
  }
  printf("%d\n", sum<=t? i: -1);

  return 0;
}


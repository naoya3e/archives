#include <stdio.h>

#define N 10
#define SENTINEL 1000000005

void show(int list[]) {
  int i;

  for (i=0; i<N; i++) {
    printf("%d ", list[i]);
  }
  printf("\n");
}

void merge(int list[], int left, int mid, int right) {
  int i, j, k;
  int n1 = mid-left;
  int n2 = right-mid;
  int L[n1+1], R[n2+1];

  for (i=0; i<n1; i++) L[i] = list[left+i];
  for (i=0; i<n2; i++) R[i] = list[mid+i];

  L[n1] = R[n2] = SENTINEL;

  i = j = 0;

  for (k=left; k<right; k++) {
    if (L[i] <= R[j]) {
      list[k] = L[i];
      i++;
    } else {
      list[k] = R[j];
      j++;
    }
  }
}

void mergeSort(int list[], int left, int right) {
  int mid;

  if (right  -left <= 1) return;

  mid = (left + right) / 2;

  mergeSort(list, left, mid);
  mergeSort(list, mid, right);

  merge(list, left, mid, right);
}

int main() {
  int list[N] = {1, 8, 4, 5, 7, 2, 3, 9, 0, 6};

  show(list);
  mergeSort(list, 0, N);
  show(list);

  return 0;
}


#include <stdio.h>
#include <stdlib.h>

// 変数 x, y, z
#define N 3

void gauss(double a[N][N+1]);  // ガウス・ジョルダン法による演算実行/出力

int main(void) {
  int i;
  double a[N][N+1];
  FILE *fp;

  if ((fp = fopen("input.txt", "r")) == NULL) {
    fprintf(stderr, "ERROR: ファイルが正常に読み込まれませんでした\n");
    exit(EXIT_FAILURE);
  }

  // ファイルから方程式を読み込み行列を生成する
  for (i=0; i<N; i++) {
    fscanf(fp, "%lf,%lf,%lf,%lf", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
  }

  // 連立方程式を出力
  for (i=0; i<N; i++) {
    printf("%fx+%fy+%fz = %f\n", a[i][0], a[i][1], a[i][2], a[i][3]);
  }

  // 演算実行
  gauss(a);

  return 0;
}

void gauss(double a[N][N+1]) {
  int i, j, k;
  int pivot;
  int coef;

  for (i=0; i<N; i++) {
    // ピボットの指定
    pivot = a[i][i];

    // ピボット行の係数を1にする
    for (j=i; j<N; j++) {
      a[i][j] /= pivot;
    }

    // 掃き出し
    for (k=0; k<N; k++) {
      if (k != i) {
        coef = a[k][i];
        for (j=i; j<N; j++) {
          a[k][j] = a[k][i] - coef * a[i][j];
        }
      }
    }
  }

  // 結果出力
  for (i=0; i<N; i++) {
    printf("x = %f\ny = %f\nz = %f\n", a[i][N]);
  }
}


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
    printf("%.1fx+%.1fy+%.1fz = %.1f\n", a[i][0], a[i][1], a[i][2], a[i][3]);
  }

  // 演算実行
  gauss(a);

  return 0;
}

void gauss(double a[N][N+1]) {
  int i, j, k;
  double pivot;
  double coef;

  for (k=0; k<N; k++) {
    // ピボットの指定 ピボットは対角成分を選択する
    pivot = a[k][k];

    // ピボット行の係数を1にする
    for (j=0; j<N+1; j++) {
      a[k][j] /= pivot;
    }

    // 掃き出し
    for (i=0; i<N; i++) {
      if (i != k) {
        coef = a[i][k];
        for (j=0; j<N+1; j++) {
          a[i][j] -= coef * a[k][j];
        }
      }
    }
  }

  // 結果出力
  printf("x = %f\ny = %f\nz = %f\n", a[0][N], a[1][N], a[2][N]);
}


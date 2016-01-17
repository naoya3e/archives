#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT  5

/*
 *
 * 0: 死亡
 * 1: 生命Aが生存
 * 2: 生命Bが生存
 *
 * 正: 周囲の生命Aの生存数
 * 負: 周囲の生命Bの生存数
 *
 */

void init_cell(int cell[][WIDTH+2], FILE *fp);
void print_board(int cell[][WIDTH+2]);
void count_neighbor(int cell[][WIDTH+2], int neightbor[][WIDTH+2]);
void next_cell(int cell[][WIDTH+2], int neightbor[][WIDTH+2]);

int main(void) {
  int i;
  int n = 3;
  int cell[HEIGHT+2][WIDTH+2]        = {0};
  int neightbor[HEIGHT+2][WIDTH+2] = {0};
  FILE *fp;

  if ((fp = fopen("extension.txt", "r")) == NULL) {
    fprintf(stderr, "ERROR: ファイルが正常に読み込まれませんでした\n");
    exit(EXIT_FAILURE);
  }

  init_cell(cell, fp);
  print_board(cell);

  for (i=0; i<n; i++) {
    count_neighbor(cell, neightbor);
    next_cell(cell, neightbor);
    print_board(cell);
    sleep(1);  // 1 sec waiting
  }

  fclose(fp);

  return 0;
}

// フィールドの初期化
void init_cell(int cell[][WIDTH+2], FILE *fp) {
  int x, y;
  int n;

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      fscanf(fp, "%d", &n);
      cell[y][x] = n;
    }
  }
}

void print_board(int cell[][WIDTH+2]) {
  int x, y;

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      switch (cell[y][x]) {
        case 0:
          printf("□ ");
          break;
        case 1:
          printf("■ ");
          break;
        case 2:
          printf("◆ ");
          break;
        default:
          fprintf(stderr, "ERROR: 不正な値がフィールドに入力されています\n");
          exit(EXIT_FAILURE);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void count_neighbor(int cell[][WIDTH+2], int neightbor[][WIDTH+2]) {
  int i;
  int x, y;
  int a = 0;
  int b = 0;
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      for (i=0; i<8; i++) {
        switch (cell[y+dy[i]][x+dx[i]]) {
          case 0:
            break;
          case 1:
            a++;
            break;
          case 2:
            b++;
            break;
          default:
            fprintf(stderr, "ERROR: 不正な値がフィールドに入力されています\n");
            exit(EXIT_FAILURE);
        }
      }

      neightbor[y][x] = (a < b)? -1*b: a;
    }
  }
}

void next_cell(int cell[][WIDTH+2], int neightbor[][WIDTH+2]) {
  int x, y;

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      if (neightbor[y][x] > 0) {
        cell[y][x] = (neightbor[y][x] == 3)? 1: (neightbor[y][x] == 2)? cell[y][x]: 0;
      } else {
        cell[y][x] = (neightbor[y][x] == -3)? 2: (neightbor[y][x] == -2)? cell[y][x]: 0;
      }
    }
  }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT 10

void init_cell(int cell[][WIDTH+2]);
void print_board(int cell[][WIDTH+2]);
void count_neighbor(int cell[][WIDTH+2], int neightbor[][WIDTH+2]);
void next_cell(int cell[][WIDTH+2], int neightbor[][WIDTH+2]);

int main(void) {
  int i;
  int n = 3;
  int cell[HEIGHT+2][WIDTH+2]      = {0};
  int neightbor[HEIGHT+2][WIDTH+2] = {0};

  init_cell(cell);
  print_board(cell);

  for (i=0; i<n; i++) {
    count_neighbor(cell, neightbor);
    next_cell(cell, neightbor);
    print_board(cell);
    sleep(2);
  }

  return 0;
}

// フィールドの初期化
void init_cell(int cell[][WIDTH+2]) {
  cell[HEIGHT/2-1][WIDTH/2+1] = 1;
  cell[HEIGHT/2  ][WIDTH/2-1] = 1;
  cell[HEIGHT/2  ][WIDTH/2+1] = 1;
  cell[HEIGHT/2+1][WIDTH/2  ] = 1;
  cell[HEIGHT/2+1][WIDTH/2+2] = 1;
  cell[HEIGHT/2+2][WIDTH/2  ] = 1;
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
  int exists = 0;
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      for (i=0; i<8; i++) {
        if (cell[y+dy[i]][x+dx[i]] == 1) exists++;
      }
      neightbor[y][x] = exists;
      exists = 0;
    }
  }
}

void next_cell(int cell[][WIDTH+2], int neightbor[][WIDTH+2]) {
  int x, y;

  for (y=1; y<=HEIGHT; y++) {
    for (x=1; x<=WIDTH; x++) {
      cell[y][x] = (neightbor[y][x] == 3)? 1: (neightbor[y][x] == 2)? cell[y][x]: 0;
    }
  }
}


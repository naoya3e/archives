#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE  9  // 盤面の大きさ
#define TERR 52  //

#define OPEN  0  // 場に存在
#define WHITE 1  // 白プレイヤー保持
#define RED   2  // 赤プレイヤー保持
#define DECK  3  // 山札として存在

typedef struct {
  int turn;
  int board[9][9];
  int x, y;
  int card[27];
  int w_knight, r_knight;
} PHASE;

void print_board(PHASE *p);
void change_board(PHASE *p, int move);

int input_move(PHASE *p);

int main() {

  while (1) {
  }

  return 0;
}

void print_board(PHASE *p) {
  int x, y;

  // 相手プレイヤーの手札表示

  // 盤面の表示
  for (y=0; y<SIZE; y++) {
    printf("   +---+---+---+---+---+---+---+---+---+\n");
    printf(" %d ", y+1);
    for (x=0; x<SIZE; x++) {
      switch (p->board[y][x]) {
        case OPEN:
        case WHITE:
        case RED:
        case DECK:
        default:
          fprintf(stderr, "ERROR: 盤面に不正な値が入力されています\n");
          exit(EXIT_FAILURE);
      }
    }
  }

  // 自分の手札表示
}


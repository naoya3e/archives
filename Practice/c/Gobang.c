#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH  7
#define HEIGHT 7
#define STONE  5

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define FIRST  1
#define SECOND 2

typedef struct {
  int turn;
  int board[HEIGHT][WIDTH];
} PHASE;

void init_board(PHASE *p);
void print_board(PHASE *p);
void change_phase(PHASE *p, int x, int y);

int check_move(PHASE *p, int x, int y);
int check_end(PHASE *p);
int check_five(PHASE *p, int x, int y);
int select_phase();

int main(void) {
  int x, y;
  int player;
  int status = 0;
  PHASE p;

  player = select_phase();

  printf("\n====== ゲームを開始します ======\n\n");

  init_board(&p);
  print_board(&p);

  // メインルーチン
  do {
    printf("\n石を置く座標を指定してください (x,y)：");
    scanf("%d,%d", &x, &y);

    if (check_move(&p, x, y)) {
      change_phase(&p, x, y);
    }

    print_board(&p);

    status = check_end(&p);
  } while (status == 0);

  if (status == FIRST) {
    printf("先手の勝利です\n");
  } else {
    printf("後手の勝利です\n");
  }

  printf("\n====== ゲームを終了します ======\n");

  return 0;
}

void init_board(PHASE *p)  {
  p->turn = BLACK;  // 先手スタート
  memset(p->board, EMPTY, sizeof(p->board));  // フィールド初期化
}

void print_board(PHASE *p) {
  int x, y;

  printf("\n     1   2   3   4   5   6   7\n");
  for (y=0; y<HEIGHT; y++) {
    printf("   +---+---+---+---+---+---+---+\n");
    printf(" %d ", y+1);
    for (x=0; x<HEIGHT; x++) {
      switch (p->board[y][x]) {
        case EMPTY:
          printf("|   ");
          break;
        case BLACK:
          printf("| ● ");
          break;
        case WHITE:
          printf("| ○ ");
          break;
        default:
          fprintf(stderr, "ERROR: 不正な値がPHASE構造体に入力されています\n");
          exit(EXIT_FAILURE);
      }
    }
    printf("|\n");
  }
  printf("   +---+---+---+---+---+---+---+\n");
}

void change_phase(PHASE *p, int x, int y) {
  p->board[y-1][x-1] = p->turn;  // フィールド更新
  p->turn = (p->turn == BLACK)? WHITE: BLACK;  // ターン交代
}

int check_move(PHASE *p, int x, int y) {
  return (x>0 && x<=WIDTH && y>0 && y<=HEIGHT && p->board[y][x]==0)? 1: 0;
}

int check_end(PHASE *p) {
  int x, y;

  for (y=0; y<HEIGHT; y++) {
    for (x=0; x<WIDTH; x++) {
      if (p->board[y][x] == EMPTY) continue;
      if (check_five(p, x, y)) return p->board[y][x];
    }
  }

  return 0;
}

int check_five(PHASE *p, int x, int y) {
  int i, j, flag = 1;
  int dx[] = {0, 1, 1};
  int dy[] = {1, 0, 1};

  for (i=0; i<3; i++) {
    for (j=1; j<=STONE-1; j++) {
      if (p->board[y][x] != p->board[y+j*dy[i]][x+j*dx[i]]) {
        flag = 0;
        break;
      }
    }
    if (flag == 1) return 1;
  }

  return 0;
}

int select_phase() {
  int n;

  while (1) {
    printf("先手が後手かを選んでください (先手● :1 後手○ :2)：");
    scanf("%d", &n);
    if (n == FIRST || n == SECOND) break;
  }

  return n;
}


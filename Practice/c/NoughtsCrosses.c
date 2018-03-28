#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH  3  // 盤面幅
#define HEIGHT 3  // 盤面高
#define STONE  3  // 連続石数

#define EMPTY 0  // 空白
#define BLACK 1  // 黒石
#define WHITE 2  // 白石

#define FIRST  1  // 先手
#define SECOND 2  // 後手

#define SUCC 1  // 着手可能
#define FAIL 0  // 着手不可能

typedef struct {
  int turn;  // 現在の手番
  int board[HEIGHT][WIDTH];  // 現在の盤面
} PHASE;

void init_board(PHASE *p);
void print_board(PHASE *p);
void change_phase(PHASE *p, int x, int y);
void find_move(PHASE *p, int moves[][WIDTH]);

int select_phase();
int check_move(PHASE *p, int x, int y);
int check_end(PHASE *p);
int check_five(PHASE *p, int x, int y);
int check_win(PHASE *p, int myturn);

int main(void) {
  int x, y;  // 着手想定座標
  int humanTurn;  // 人間の操作する手番
  int cpuTurn;  // AIの操作する手番
  int status = 0;  // 0:ゲーム続行 1:先手勝利 2:後手勝利
  int moves[HEIGHT][WIDTH];  // 着手可能盤面
  PHASE p;

  srand((unsigned int)time(NULL));

  humanTurn = select_phase();

  printf("\n====== ゲームを開始します ======\n\n");

  init_board(&p);
  print_board(&p);

  while(1) {
    if (p.turn == humanTurn) {
      printf("\n石を置く座標を指定してください (x,y)：");
      scanf("%d,%d", &x, &y);
    } else {
      find_move(&p, moves);
      x = rand()%WIDTH;
      y = rand()%HEIGHT;
      // cpu(&p, &x, &y, humanTurn);
    }

    if (check_move(&p, x, y)) {
      change_phase(&p, x, y);
    } else {
      continue;
    }

    print_board(&p);

    status = check_end(&p);
    if (status != 0) break;
  }

  if (status == FIRST) {
    printf("先手の勝利です\n");
  } else {
    printf("後手の勝利です\n");
  }

  printf("\n====== ゲームを終了します ======\n");

  return 0;
}

void init_board(PHASE *p)  {
  p->turn = FIRST;  // 先手スタート
  memset(p->board, EMPTY, sizeof(p->board));  // フィールド初期化
}

void print_board(PHASE *p) {
  int x, y;

  printf("\n     1   2   3\n");
  for (y=0; y<HEIGHT; y++) {
    printf("   +---+---+---+\n");
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
  printf("   +---+---+---+\n");
}

void change_phase(PHASE *p, int x, int y) {
  p->board[y-1][x-1] = p->turn;  // フィールド更新
  p->turn = (p->turn == BLACK)? WHITE: BLACK;  // ターン交代
}

void find_move(PHASE *p, int moves[][WIDTH]) {
  int x, y;

  for (y=0; y<HEIGHT; y++) {
    for (x=0; x<WIDTH; x++) {
      moves[y][x] = (p->board[y][x] == 0)? 1: 0;
    }
  }
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

int check_move(PHASE *p, int x, int y) {
  return (x>0 && x<=WIDTH && y>0 && y<=HEIGHT && p->board[y-1][x-1]==0)? 1: 0;
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
    if (x+dx[i] >= WIDTH)  continue;
    if (y+dy[i] >= HEIGHT) continue;
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

int check_win(PHASE *p, int myturn) {

}


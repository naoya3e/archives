#include "noughts.h"

void initialize(PHASE *p, int *humanTurn) {
  int n;

  printf("######################################\n");
  printf("             三目並べ PvE             \n");
  printf("######################################\n\n");

  while (1) {
    printf("あなたの手番を選択してください (先手:1 後手:2) >> ");
    scanf("%d", &n);

    if (n != BLACK && n != WHITE) {
      printf("入力できる数字は 1 か 2 のみです\n");
      printf("再度、入力を行ってください\n\n");
    } else {
      break;
    }
  }

  if (n == FIRST) {
    printf("あなたは先手で石の色は● です\n\n");
    *humanTurn = FIRST;
  } else {
    printf("あなたは後手で石の色は○ です\n\n");
    *humanTurn = SECOND;
  }

  init_board(p);  // ターンと盤面の初期化

  printf("ゲームを開始します\n\n");

  print_board(p);  // １回目は必ず盤面を表示する
}

void finalize(PHASE *p, int status) {
  switch (status) {
    case WIN_F:
      printf("先手の勝利です\n");
      break;
    case WIN_S:
      printf("後手の勝利です\n");
      break;
    case FIN:
      printf("引き分けです\n");
      break;
    default:
      fprintf(stderr, "ERROR: 不正な値がステータスに入力されています\n");
  }
}

void init_board(PHASE *p) {
  p->turn = FIRST;  // 先手からゲーム開始
  memset(p->board, EMPTY, sizeof(p->board));  // 盤面を空白で初期化
}

void print_board(PHASE *p) {
  int x, y;

  printf("     1   2   3\n");  // 行番号 (x座標)
  for (y=0; y<SIZE; y++) {
    printf("   +---+---+---+\n");
    printf(" %d ", y+1);
    for (x=0; x<SIZE; x++) {
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
          fprintf(stderr, "ERROR: 不正な値が盤面に入力されています\n");
          exit(EXIT_FAILURE);
      }
    }
    printf("|\n");
  }
  printf("   +---+---+---+\n\n");
}

void human(PHASE *p) {
  int x, y;

  while (1) {
    printf("石を置く座標を指定してください (x,y) >> ");
    scanf("%d,%d", &x, &y);

    // 着手が有効であれば局面の更新のためbreakする
    if (check_move(p, x, y)) break;
  }

  // 表示調整用
  printf("\n");

  change_phase(p, x, y);
}

void cpu(PHASE *p) {
  int x, y;

  while (1) {
    x = rand()%SIZE;
    y = rand()%SIZE;
    if (check_move(p, x, y)) break;
  }

  change_phase(p, x, y);
}

int check_move(PHASE *p, int x, int y) {
  // 入力座標の領域参照が正常かどうか
  if (x < 1 || x > SIZE || y < 1 || y >SIZE) {
    fprintf(stderr, "ERROR: 指定した座標に石は置けません\n\n");
    return FAIL;
  }

  // 入力座標に着手が可能かどうか
  if (p->board[y-1][x-1] != EMPTY) {
    fprintf(stderr, "ERROR: 指定した座標に石がすでに存在します\n\n");
    return FAIL;
  }

  // 入力座標は正常である
  return SUCC;
}

int check_end(PHASE *p) {
  int x, y;
  int skipped = 0;

  // 盤面を全探索してヒットした石から 下, 右, 右下, 左下 を探索する
  for (y=0; y<SIZE; y++) {
    for (x=0; x<SIZE; x++) {
      if (p->board[y][x] == EMPTY) { // 空白は探索対象外
        skipped++;
        continue;
      }
      if (check_five(p, x, y)) return p->board[y][x];
    }
  }

  // 引き分けか続行の状況のみここまで到達する
  return (skipped > 0)? CONT: FIN;
}

int check_five(PHASE *p, int x, int y) {
  int i, j;
  int flag;
  int dx[] = {0, 1, 1, -1};
  int dy[] = {1, 0, 1,  1};


  for (i=0; i<4; i++) {  // 探索方向を操作するループ
    flag = SUCC;
    // 基準座標から探索方向へ違う石が見つかれば連続していないとみなす
    for (j=1; j<STONE; j++) {
      if (x + j*dx[i] >= SIZE || y + j*dy[i] >= SIZE) {
        flag = FAIL;
        break;
      }

      if (p->board[y][x] != p->board[y + j*dy[i]][x + j*dx[i]]) {
        flag = FAIL;
        break;
      }
    }
    if (flag == SUCC) return SUCC;
  }

  return FAIL;
}

void change_phase(PHASE *p, int x, int y) {
  p->board[y-1][x-1] = p->turn;  // 指定座標を現在のプレイヤーの石にする
  p->turn = (p->turn == FIRST)? SECOND: FIRST;  // ターン交代
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE  9  // 盤面の大きさ
#define TERR 52  // 領土の合計値到達数

#define HANDS 5  // 手札の枚数
#define CARDS 24 // 移動カードの枚数

#define EMPTY 0  // 盤面が空白

#define DRAW  3  // 引き分け

#define USED  0  // 場
#define WHITE 1  // CPU
#define RED   2  // プレイヤー
#define DECK  3  // 山札

typedef struct {
  int turn;  // 手番のプレイヤー
  int board[SIZE][SIZE];  // 盤面
  int x, y;  // 駒の座標
  int card[CARDS];  // 移動カード
  int w_knight, r_knight;  // 騎士カード所持数
  int player_hand[HANDS];  // プレイヤーの手札
  int cpu_hand[HANDS];  // CPUの手札
} PHASE;


// 基本動作関数
void initialize(PHASE *p);

// 出力用関数
void print_board(PHASE *p);  // 盤面およびプレイヤーの手札の表示
void print_card(PHASE *p, int player);  // プレイヤーの手札の表示

// 盤面操作関数
void get_vector(PHASE *p, int index, int *scalar, int *dx);  // 入力されたインデックスから移動の大きさと向きを取得
void change_phase(PHASE *p, int nx, int ny);  // 局面を着手にしたがって更新する

// プレイヤー入力処理関数
void get_player_command(PHASE *p);  // プレイヤーのコマンド受付

// プレイヤー情報取得関数
int get_player_hands_size(PHASE *p);  // プレイヤーの手札の枚数をカウントする


int main() {
  int exectable;  // 着手が実行可能かどうか
  PHASE p;  // 局面

  initialize(&p);

  // メインルーチン
  while (1) {
    get_player_command(&p);
    print_board(&p);
    break;  // DEBUG
  }

  return 0;
}

void initialize(PHASE *p) {
  int i, n;

  printf("##################################\n");
  printf("            Rosenkönig            \n");
  printf("              対 CPU              \n");
  printf("##################################\n\n");

  // 手番の案内
  printf(" あなたは先手● (ランカスター家)です。\n");

  // 盤面の案内
  printf(" [x]:コマンド 残:残り駒数 *:駒 ● :現在の得点 ▼ :騎士の枚数 \n");

  // 乱数初期化
  srand((unsigned int)time(NULL));

  // ターン初期化
  p->turn = RED;

  // 盤面初期化
  memset(p->board, EMPTY, sizeof(p->board));

  // 駒の座標初期化
  p->x = 4;
  p->y = 4;

  // 移動カード初期化
  for (i=0; i<CARDS; i++) p->card[i] = DECK;  // 移動カードはすべて山札

  // 移動カード初期配布
  // プレイヤーカード配布
  i = 0;
  while (i<HANDS) {
    n = rand()%CARDS;
    if (p->card[n] == DECK) {
      p->card[n] = RED;
      // p->player_hand[i] = n;
      i++;
    }
  }
  // CPUカード配布
  i = 0;
  while (i<HANDS) {
    n = rand()%CARDS;
    if (p->card[n] == DECK) {
      p->card[n] = WHITE;
      // p->cpu_hand[i] = n;
      i++;
    }
  }

  // 騎士カード所持数初期化
  p->w_knight = 4;
  p->r_knight = 4;

  // ゲーム開始
  print_board(p);
}

void print_board(PHASE *p) {
  int i;
  int x, y;

  // 表示調整
  printf("\n");

  // 相手の手札表示
  print_card(p, WHITE);

  // 盤面の表示
  for (y=0; y<SIZE; y++) {
    printf(" +---+---+---+---+---+---+---+---+---+\n ");
    for (x=0; x<SIZE; x++) {
      if (x == p->x && y == p->y) {
        printf("| * ");
      } else {
        switch (p->board[y][x]) {
          case EMPTY:
            printf("|   ");
            break;
          case WHITE:
            printf("| ○ ");
            break;
          case RED:
            printf("| ● ");
            break;
          default:
            fprintf(stderr, "ERROR: 盤面に不正な値が入力されています\n");
            exit(EXIT_FAILURE);
        }
      }
    }
    // 盤面の右端の表示調整
    printf("|");

    // 相手の得点表示
    if (y == 1) printf("   ○  %3d", 100);

    // 残り駒数表示
    if (y == 4) printf("   残 %3d", 52);

    // 自分の得点表示
    if (y == 7) printf("   ●  %3d", 100);

    // 次の行へ表示を移る
    printf("\n");
  }
  printf(" +---+---+---+---+---+---+---+---+---+\n");

  // 自分の手札表示
  print_card(p, RED);

  // 表示調整
  printf("\n");
}

void print_card(PHASE *p, int player) {
  int i, j;
  char *arrow[8] = {"↖ ", "↑ ", "↗ ", "← ", "→ ", "↙ ", "↓ ", "↘ "};

  // コマンド番号表示
  if (player == RED) {
    for (i=0; i<HANDS; i++) {
      printf("  [%d]", i+1);
    }
    printf("\n");
  }

  // カード表示
  for (i=0; i<CARDS; i++) {
    if (p->card[i] == player) printf("  %d%s", i/8+1, arrow[i%8]);
  }

  // 残りの騎士カードの枚数表示
  if (player == RED) {
    printf("      ▼ %d\n", p->r_knight);
  } else {
    printf("      △ %d\n", p->w_knight);
  }
}

void get_vector(PHASE *p, int index, int *coef, int *dirc) {
  int i;
  int n = 0;

  for (i=0; i<CARDS; i++) {
    if (p->card[i] == p->turn) n++;
    if (n == index) break;
  }

  *coef = i/8+1;
  *dirc = i%8;
}

void change_phase(PHASE *p, int nx, int ny) {
  p->x = nx;
  p->y = ny;
}

void get_player_command(PHASE *p) {
  int n;
  int coef, dirc;  // 移動ベクトルの係数(大きさ)と向き
  int nx, ny;  // 移動先の座標
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  printf("1~5:駒を移動する 0:カードを引く >> ");

  while (1) {
    scanf("%d", &n);

    // コマンドが想定範囲内の値をとっているかどうか
    if (n < 0 || n > 5) {
      printf("1~5 もしくは 0 だけが入力可能なコマンドです >> ");
      continue;
    }

    // 手札が5枚のときはカードを新たに引くことはできない
    if (n == 0 && get_player_hands_size(p) == 5) {
      printf("手札が5枚あるため新たに引くことはできません >> ");
      continue;
    }

    // 移動コマンドであれば、移動可能かどうかシミュレート
    if (n >= 1 && n <= 5) {
      get_vector(p, n, &coef, &dirc);

      // 移動先の座標算出
      nx = p->x + coef*dx[dirc];
      ny = p->y + coef*dy[dirc];

      // x方向を探索
      if (nx < 0 || nx >= SIZE) {
        printf("盤面外への移動は行えません\n");
        continue;
      }
      // y方向を探索
      if (ny < 0 || ny >= SIZE) {
        printf("盤面外への移動は行えません\n");
        continue;
      }
    }

    // コマンドが実行可能である
    break;
  }

  // 入力コマンドに基づき局面の更新を行う
  change_phase(p, nx, ny);
}

int get_player_hands_size(PHASE *p) {
  int i;
  int n = 0;

  for (i=0; i<CARDS; i++) {
    if (p->card[i] == p->turn) n++;
  }

  return n;
}


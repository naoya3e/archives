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

void initialize(PHASE *p);

void print_board(PHASE *p);  // 盤面およびプレイヤーの手札の表示
void print_card(PHASE *p, int player);  // プレイヤーの手札の表示
void index_hand_from_deck(PHASE *p);  // 山札から手札をインデックスする
void change_board(PHASE *p, int move);  // 盤面と駒の更新
void deal_card(PHASE *p);  // 山札からカードを配布

void get_player_command(PHASE *p);  // プレイヤーのコマンド受付

int input_move(PHASE *p);  // プレイヤーの着手入力
int check_end(PHASE *p);  // 終了判定
int judge(PHASE *p);  // 勝敗判定

int main() {
  int exectable;  // 着手が実行可能かどうか
  PHASE p;  // 局面

  initialize(&p);

  // // メインルーチン
  // while (1) {
  // }

  return 0;
}

void initialize(PHASE *p) {
  int i, n;

  printf("##################################\n");
  printf("            Rosenkonig            \n");
  printf("              対 CPU              \n");
  printf("##################################\n\n");

  // 手番の案内
  printf(" あなたは先手で● です。\n");

  // 盤面の案内
  printf(" [x]:コマンド 残:残り駒数 *:駒 ● :現在の得点 ▼ :騎士の枚数 \n\n");

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

  // 相手プレイヤーの手札表示
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
    printf("|\n");
  }
  printf(" +---+---+---+---+---+---+---+---+---+\n");

  // 自分の手札表示
  print_card(p, RED);
}

void print_card(PHASE *p, int player) {
  int i;
  char *arrow[8] = {"↖ ", "↑ ", "↗ ", "← ", "→ ", "↙ ", "↓ ", "↘ "};

  // コマンド番号表示
  if (player == RED) {
    for (i=0; i<HANDS; i++) {
      printf("  [%d]", i);
    }
    printf("\n");
  }

  // カード表示
  for (i=0; i<HANDS; i++) {
    printf("  %d%s", 3, "→ ");
  }
  printf("\n");
}


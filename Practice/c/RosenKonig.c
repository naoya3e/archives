#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE  9  // 盤面の大きさ
#define TERR 52  // 領土の合計値到達数

#define HANDS 5  // 手札の枚数
#define CARDS 27 // 移動カードの枚数

#define EMPTY 0  // 盤面が空白

#define DRAW  3  // 引き分け

#define OPEN  0  // 場
#define WHITE 1  // 白プレイヤー
#define RED   2  // 赤プレイヤー
#define DECK  3  // 山札

typedef struct {
  int turn;  // 手番のプレイヤー
  int board[SIZE][SIZE];  // 盤面
  int x, y;  // 駒の座標
  int card[CARDS];  // 移動カード
  int w_knight, r_knight;  // プレイヤーの騎士カード所持数
} PHASE;

void initialize(PHASE *p);

void print_board(PHASE *p);  // 盤面およびプレイヤーの手札の表示
void print_card(PHASE *p, int player);  // プレイヤーの手札の表示
void change_board(PHASE *p, int move);  // 盤面と駒の更新
void deal_card(PHASE *p);  // 山札からカードを配布

int input_move(PHASE *p);  // プレイヤーの着手入力
int check_end(PHASE *p);  // 終了判定
int judge(PHASE *p);  // 勝敗判定

int main() {
  PHASE p;  // 局面

  initialize(&p);

  // メインルーチン
  // while (1) {
  // }

  return 0;
}

void initialize(PHASE *p) {
  int i;
  int n;
  int counter;

  printf("############################\n");
  printf("#        Rosenkonig        #\n");
  printf("############################\n");

  while (1) {
    printf("あなたの手番を選択してください (先手:1 後手:2) >> ");
    scanf("%d", &n);

    if (n != WHITE && n != RED) {
      printf("入力できる数字は 1 か 2 のみです\n");
      printf("再度、入力を行って下さい\n\n");
    } else {
      break;
    }
  }

  // 乱数初期化
  srand((unsigned int)time(NULL));

  // ターン初期化
  p->turn = n;

  // 盤面初期化
  memset(p->board, EMPTY, sizeof(p->board));

  // 駒の座標初期化
  p->x = 4;
  p->y = 4;

  // 移動カード初期化
  for (i=0; i<CARDS; i++) p->card[i] = DECK;  // 移動カードはすべて山札
  counter = 0;
  while (counter < HANDS) {
    n = rand()%CARDS;
    if (p->card[n] == DECK) {
      p->card[n] = WHITE;
      counter++;
    }
  }
  counter = 0;
  while (counter < HANDS) {
    n = rand()%CARDS;
    if (p->card[n] == DECK && n%9 != 4) {
      p->card[n] = RED;
      counter++;
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
    printf("   +---+---+---+---+---+---+---+---+---+\n");
    printf(" %d ", y+1);
    for (x=0; x<SIZE; x++) {
      if (x == p->x && y == p->y) {
        printf("| ＊");
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
  printf("   +---+---+---+---+---+---+---+---+---+\n");

  // 自分の手札表示
  print_card(p, RED);
}

void print_card(PHASE *p, int player) {
  int i;
  int scalar[5] = {0};
  int dx[5] = {0};
  char *arrow[8] = {"↖ ", "↑ ", "↗ ", "← ", "", "→ ", "↙ ", "↓ ", "↘ "};

  for (i=0; i<27; i++) {
    if (p->card[i] == player) {
      switch (i%9) {
        case 0:
          printf("↖ ");
          break;
        case 1:
          printf("↑ ");
          break;
        case 2:
          printf("↗ ");
          break;
        case 3:
          printf("← ");
          break;
        case 4:
          break;
        case 5:
          printf("→ ");
          break;
        case 6:
          printf("↙ ");
          break;
        case 7:
          printf("↓ ");
          break;
        case 8:
          printf("↘ ");
          break;
        default:
          fprintf(stderr, "ERROR: 移動カードに不正な値が入力されています\n");
          exit(EXIT_FAILURE);
      }
    }
  }
  printf("\n\n");
}


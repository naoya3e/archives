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

#define KEEP  -1  // 移動させない
#define USED   0  // 場
#define WHITE  1  // CPU
#define RED    2  // プレイヤー
#define DECK   3  // 山札

typedef struct {
  int turn;  // 手番
  int board[SIZE][SIZE];  // 盤面
  int x, y;  // 駒の座標
  int card[CARDS];  // 移動カード
  int w_knight, r_knight;  // 騎士カード所持数
} PHASE;


// 基本動作関数
void initialize(PHASE *p);

// 出力用関数
void print_board(PHASE *p);  // 盤面および手札の表示
void print_card(PHASE *p, int player);  // 手札の表示

// 盤面操作関数
int get_vector(PHASE *p, int index, int *scalar, int *dx);  // 入力されたインデックスから移動の大きさと向きを取得
void change_phase(PHASE *p, int move);  // 局面を着手にしたがって更新する

// 札操作関数
void deal_card(PHASE *p);  // 山札からランダムにカードを配布する

// プレイヤー入力処理関数
void input_move(PHASE *p);  // プレイヤーのコマンド受付

// プレイヤー情報取得関数
int get_player_hand_size(PHASE *p);  // プレイヤーの手札の枚数をカウントする


int main() {
  int exectable;  // 着手が実行可能かどうか
  PHASE p;  // 局面

  initialize(&p);

  // メインルーチン
  while (1) {
    // プレイヤーターン
    input_move(&p);
    print_board(&p);

    // CPUターン
    input_move(&p);
    print_board(&p);

    // break;  // DEBUG
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
  printf(" あなたは先手● です。\n");

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
      i++;
    }
  }
  // CPUカード配布
  i = 0;
  while (i<HANDS) {
    n = rand()%CARDS;
    if (p->card[n] == DECK) {
      p->card[n] = WHITE;
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
  int i;
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

int get_vector(PHASE *p, int index, int *coef, int *dirc) {
  int i;
  int n = 0;

  // index番目のカードを探索する
  for (i=0; i<CARDS; i++) {
    if (p->card[i] == p->turn) n++;
    if (n == index) break;
  }

  // カードの添字から移動カードの大きさと向きを算出する
  *coef = i/8+1;
  *dirc = i%8;

  // 移動カードを戻り値とし、change_phase()で利用する
  return i;
}

void change_phase(PHASE *p, int move) {
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  // カードを手札に加えたときは、駒の移動を行わない
  if (move != KEEP) {
    // 現在の駒の位置から移動
    p->x += (move/8+1)*dx[move%8];
    p->y += (move/8+1)*dy[move%8];

    // 使用したカードを手札から外す
    p->card[move] = USED;
  }

  // 盤面の領土を反映させる
  p->board[p->y][p->x] = p->turn;

  // ターンを交代する
  p->turn = (p->turn == RED)? WHITE: RED;
}

void deal_card(PHASE *p) {
  int i, n;
  int counter = 0;

  // 山札の存在確認
  for (i=0; i<CARDS; i++) {
    if (p->card[i] == DECK) counter++;
  }

  // 山札が0枚であったなら、使用済カードを山札に戻す
  if (counter == 0) {
    for (i=0; i<CARDS; i++) {
      if (p->card[i] == USED) p->card[i] = DECK;
    }
  }

  // 山札からカードを一枚引き、手番の手札とする
  while (1) {
    n = rand()%CARDS;
    if (p->card[n] == DECK) {
      p->card[n] = p->turn;
      break;
    }
  }
}

void input_move(PHASE *p) {
  int n;
  int move;  // 一次元で表される移動データ
  int coef, dirc;  // 移動ベクトルの係数(大きさ)と向き
  int nx, ny;  // 移動先の座標
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  printf(" 1~5:駒を移動する 0:カードを引く >> ");

  while (1) {
    scanf("%d", &n);

    // コマンドが想定範囲内の値をとっているかどうか
    if (n < 0 || n > 5) {
      printf("1~5 もしくは 0 だけが入力可能なコマンドです >> ");
      continue;
    }

    // 手札が5枚のときはカードを新たに引くことはできない
    if (n == 0 && get_player_hand_size(p) == 5) {
      printf("手札が5枚あるため新たに引くことはできません >> ");
      continue;
    }

    // 移動コマンドであれば、移動可能かどうかシミュレート
    if (n >= 1 && n <= 5) {
      move = get_vector(p, n, &coef, &dirc);

      // 移動先の座標算出
      nx = p->x + coef*dx[dirc];
      ny = p->y + coef*dy[dirc];

      // x方向を探索
      if (nx < 0 || nx >= SIZE) {
        printf("盤面外への移動は行えません >> ");
        continue;
      }
      // y方向を探索
      if (ny < 0 || ny >= SIZE) {
        printf("盤面外への移動は行えません >> ");
        continue;
      }
    }

    // 札のドローコマンドであり、手札の枚数が4枚以下であるか
    if (n == 0 && get_player_hand_size(p) < 5) {
      // カードを1枚手札に加える
      deal_card(p);

      // 移動を防ぐために -1 フラグを立てる
      move = KEEP;
    }

    // コマンドが実行可能である
    break;
  }

  // 入力コマンドに基づき局面の更新を行う
  change_phase(p, move);
}

int get_player_hand_size(PHASE *p) {
  int i;
  int n = 0;

  for (i=0; i<CARDS; i++) {
    // 自分の手札であったらカウンタを増やす
    if (p->card[i] == p->turn) n++;
  }

  return n;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE  9  // 盤面の大きさ
#define TERR 52  // 領土の合計値到達数

#define HANDS 5  // 手札の枚数
#define CARDS 24 // 移動カードの枚数

#define EMPTY 0  // 盤面が空白

#define SEARCH 1  // 探索対象かつ連結対象
#define NOCALC 2  // 探索対象ではあるが連結対象ではない

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
// void finalize(PHASE *p);

// 出力用関数
void print_board(PHASE *p);  // 盤面および手札の表示
void print_card(PHASE *p, int player);  // 手札の表示

// 勝敗判定関数
int check_end(PHASE *p);  // ゲームが終了したかどうかを判定
int judge(PHASE *p);  // 盤面から勝敗判定を行う

// 盤面操作関数
int get_vector(PHASE *p, int index, int *scalar, int *dx);  // 入力されたインデックスから移動の大きさと向きを取得
int get_territory_length(PHASE *p);  // 盤面から領土とされた数をカウントする
int calc_point(PHASE *p, int turn);  // 盤面から得点を計算する
void change_phase(PHASE *p, int move);  // 局面を着手にしたがって更新する

// 札操作関数
void deal_card(PHASE *p);  // 山札からランダムにカードを配布する

// プレイヤー入力処理関数
void input_move(PHASE *p);  // プレイヤーのコマンド受付

// プレイヤー情報取得関数
int get_player_hand_size(PHASE *p);  // プレイヤーの手札の枚数をカウントする

// CPU動作処理関数
int select_move(PHASE *p);  // CPUは最大得点となる着手を選択する


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

    // 終了条件を満たしていればメインルーチンを脱する
    if (check_end(&p)) break;
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
    if (y == 1) printf("   ○  %3d", calc_point(p, WHITE));

    // 残り駒数表示
    if (y == 4) printf("   残 %3d", TERR-get_territory_length(p));

    // 自分の得点表示
    if (y == 7) printf("   ●  %3d", calc_point(p, RED));

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

int check_end(PHASE *p) {
  int terr;

  // 占領した領土数が52になったらゲーム終了
  terr = get_territory_length(p);
  return (terr == TERR)? 1: 0;

  // TODO: どちらの手番でも着手不可能であればゲーム終了条件を満たす
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

int get_territory_length(PHASE *p) {
  int i, j;
  int n = 0;

  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      // 盤面が白または赤の領土であればカウントアップ
      if (p->board[j][i] == WHITE || p->board[j][i] == RED) n++;
    }
  }

  return n;
}

int calc_point(PHASE *p, int turn) {
  int i, j;
  int x_status = 1, y_status = 1;  // 探索状況
  int point = 0;  // 得点の合計値
  int connected = 1;  // 連結数
  int target[SIZE][SIZE] = {0};  // 探索対象のみを抽出し格納する配列

  // 手番の領土を抽出する
  //    1:探索対象の領土 0:探索対象外もしくは探索済み領土
  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      if (p->board[j][i] == turn) target[j][i] = SEARCH;
    }
  }

  // 盤面を全探索する
  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      // 手番の領土を見つけたら連結を確認する
      if (target[j][i] == SEARCH || target[j][i] == NOCALC) {
        // 領域外参照を対策する
        if (i+1 >= SIZE) x_status = 0;
        if (j+1 >= SIZE) y_status = 0;

        // 右を探索する
        if (x_status && target[j][i+1] == SEARCH) {
          x_status = 1;
          connected++;
        } else if (x_status && target[j][i+1] == NOCALC) {
          x_status = 1;
        } else {
          x_status = 0;
        }

        // 下を探索する
        if (y_status && target[j+1][i] == SEARCH) {
          y_status = 1;
          connected++;
        } else if (y_status && target[j+1][i] == NOCALC) {
          y_status = 1;
        } else {
          y_status = 0;
        }

        // 探索した領土を探索済みにする
        target[j][i] = EMPTY;

        if (x_status == 0 && y_status == 0) {
          // 得点は連結数の2乗
          point += connected * connected;

          // 探索状況初期化
          x_status = 1;
          y_status = 1;

          // 連結数初期化
          connected = 1;
        }
      }
    }
  }

  return point;
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

    // 移動先が敵領土であれば、騎士カードをデクリメント
    if (p->board[p->y][p->x] == WHITE) p->r_knight--;
    if (p->board[p->y][p->x] == RED) p->w_knight--;

    // 盤面の領土を反映させる
    p->board[p->y][p->x] = p->turn;
  }

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

    // TODO: パスチェックが必要だな

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
    // TODO: 移動コマンドの下限・上限をget_player_hand_size()で取得すべき
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

      // 移動先が自分の領土であるかどうか
      if (p->turn == RED && p->board[ny][nx] == RED) {
        printf("自分の領土への移動は行えません >> ");
        continue;
      }
      if (p->turn == RED && p->board[ny][nx] == RED) {
        printf("自分の領土への移動は行えません >> ");
        continue;
      }

      // 騎士カードを必要とするかどうか
      if (p->board[ny][nx] == WHITE) {
        if (p->turn == RED && p->r_knight <= 0) {
          printf("騎士カードがないため占領できません >> ");
          continue;
        }
        if (p->turn == WHITE && p->w_knight <= 0) {
          printf("騎士カードがないため占領できません >> ");
          continue;
        }
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


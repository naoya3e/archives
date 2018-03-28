#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE  9  // 盤面の大きさ
#define TERR 52  // 領土の合計値到達数

#define HANDS 5  // 手札の枚数
#define CARDS 24 // 移動カードの枚数

#define EMPTY 0  // 盤面が空白

#define DO   -1  // 探索対象かつ連結対象
#define DONE -2  // 探索対象ではあるが連結対象ではない

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
int get_territory_length(PHASE *p);  // 盤面から領土とされた数をカウント
void change_phase(PHASE *p, int move);  // 局面を着手にしたがって更新

// 得点計算用関数
int calc_point(PHASE *p, int turn);  // 盤面から得点を計算
int get_sum_of_target(int target[][SIZE]);  // 2次元配列から総和を計算する
int get_n_max_from_target(int target[][SIZE]);  // 対象配列からn番目の最大連結数を得る
void create_search_target(PHASE *p, int target[][SIZE], int turn);  // 得点探索用二次元配列を作成

// 札操作関数
int check_pass(PHASE *p);  // 手札が使用可能かどうかを調べる
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
    for (i=0; i<get_player_hand_size(p); i++) {
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

int calc_point(PHASE *p, int turn) {
  int point;  // 得点の合計値
  int target[SIZE][SIZE] = {0};  // 探索対象のみを抽出し格納する配列

  // 得点計算用の2次元配列を作成
  create_search_target(p, target, turn);

  // 作成したtarget配列の総和を取ることで得点が得られる
  point = get_sum_of_target(target);

  return point;
}

int get_sum_of_target(int target[][SIZE]) {
  int i, j;
  int n = 0;

  // target[][]にはDOとDONEはすべて上書きされ連結数が格納されているはず
  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      n += target[j][i];
    }
  }

  return n;
}

int get_n_max_from_target(int target[][SIZE], int n) {
  int i, j;
  int max = 0;

  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      if (max > target[j][i]) max = target[j][i];
    }
  }

  return max;
}

void create_search_target(PHASE *p, int target[][SIZE], int turn) {
  int i, j;
  int x, y;
  int xs = 1, ys = 1;
  int connect = 1;

  // turnの領土を抽出し探索対象とする
  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      if (p->board[j][i] == turn) target[j][i] = DO;
    }
  }

  // 盤面を全探索し、探索対象と探索済みに、探索済みを連結数に更新していく
  for (j=0; j<SIZE; j++) {
    for (i=0; i<SIZE; i++) {
      if (target[j][i] == DO || target[j][i] == DONE) {
        // 全探索時に右・下について領域外参照であれば検出
        if (i+1 >= SIZE) xs = 0;
        if (j+1 >= SIZE) ys = 0;

        // 右方向1マス探索
        if (xs == 1 && target[j][i+1] == DO) {
          xs = 1;
          connect++;
        } else if (xs == 1 && target[j][i+1] == DONE) {
          xs = 1;
        } else {
          xs = 0;
        }

        // 下方向1マス探索
        if (ys == 1 && target[j+1][i] == DO) {
          ys = 1;
          connect++;
        } else if (ys == 1 && target[j+1][i] == DONE) {
          ys = 1;
        } else {
          ys = 0;
        }

        // 探索した座標を探索済みにする
        target[j][i] = DONE;

        // 連結が途切れたら探索済み座標を連結数で上書きする
        if (xs == 0 && ys == 0) {
          // 再び全探索して、探索済みを発見したら更新
          for (y=0; y<SIZE; y++) {
            for (x=0; x<SIZE; x++) {
              if (target[y][x] == DONE) target[y][x] = connect;
            }
          }

          // 探索状況初期化
          xs = 1;
          ys = 1;
          connect = 1;
        }
      }
    }
  }
}

int check_pass(PHASE *p) {
  int i;
  int gx, gy;
  int knight;
  int status = 1;

  // 騎士カードの枚数を確認
  knight = (p->turn == RED)? r_knight: w_knight;

  // 手札カードがあれば使用可能が探索
  for (i=0; i<CARDS; i++) {
    if (p->card[i] == p->turn) {
      // 移動先の座標を算出する
      gx = p->x + (i/8+1)*dx[i%8];
      gy = p->y + (i/8+1)*dy[i%8];

      if (p->board[gy][gx] != p->turn && knight > 0) {
        status *= 1;
      } else {
        status *= 0;
      }
    }
  }

  // 手札カードが0枚であれば問答無用で0を返す
  if (get_player_hand_size(p) == 0) return 0;

  return status;
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
  int max_command;  // 入力可能な最大コマンド値
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  printf(" 1~5:駒を移動する 0:カードを引く >> ");

  while (1) {
    scanf("%d", &n);

    // TODO: パスチェックが必要だな

    // コマンドが想定範囲内の値をとっているかどうか
    if (n < 0 || n > 5) {
      printf(" ERROR: 1~5 もしくは 0 だけが入力可能なコマンドです >> ");
      continue;
    }

    // 手札が5枚のときはカードを新たに引くことはできない
    if (n == 0 && get_player_hand_size(p) == 5) {
      printf(" ERROR: 手札が5枚あるため新たに引くことはできません >> ");
      continue;
    }

    // コマンドの最大値を取得する
    max_command = get_player_hand_size(p);

    // 移動コマンドだが手札が0枚である
    if (n >= 1 && n <= 5 && max_command == 0) {
      printf(" ERROR: 手札をドローしてください >> ");
      continue;
    }

    // 入力されたコマンドが手札に存在しないもとであった場合
    if (n > max_command) {
      printf(" ERROR: 入力されたコマンドが示す手札は存在しません >> ");
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
        printf(" ERROR: 盤面外への移動は行えません >> ");
        continue;
      }
      // y方向を探索
      if (ny < 0 || ny >= SIZE) {
        printf(" ERROR: 盤面外への移動は行えません >> ");
        continue;
      }

      // 移動先が自分の領土であるかどうか
      if (p->turn == RED && p->board[ny][nx] == RED) {
        printf(" ERROR: 自分の領土への移動は行えません >> ");
        continue;
      }
      if (p->turn == RED && p->board[ny][nx] == RED) {
        printf(" ERROR: 自分の領土への移動は行えません >> ");
        continue;
      }

      // 騎士カードを必要とするかどうか
      if (p->board[ny][nx] == WHITE) {
        if (p->turn == RED && p->r_knight <= 0) {
          printf(" ERROR: 騎士カードがないため占領できません >> ");
          continue;
        }
        if (p->turn == WHITE && p->w_knight <= 0) {
          printf(" ERROR: 騎士カードがないため占領できません >> ");
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

int select_move(PHASE *p) {
  int i, j, k;
  int n = 1;
  int target[SIZE][SIZE];
  int gx, gy;
  int sx[] = {0, 1, 0, -1};
  int sy[] = {-1, 0, 1, 0};
  int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

  // 連結数を得るために目標配列を取得する
  create_search_target(p, target, WHITE);

  // 最大連結数を求める
  cn = get_n_max_from_target(target, n);

  // TODO: 移動可能かどうかのチェックなくね？
  // TODO: cnをデクリメントして1まで見る必要ある気がする
  // TODO: もしcnでも見つからなければ手札からランダムに選べば良い

  for (i=0; i<CARDS; i++) {
    if (p->card[i] == WHITE) {
      // 移動先の座標を算出する
      gx = p->x + (i/8+1)*dx[i%8];
      gy = p->y + (i/8+1)*dy[i%8];

      // 移動先の上、右、下、左の順に見ていき隣接するマスが指定した連結数cnであればその座標に着手
      for (k=0; k<4; k++) {
        if (target[gy+sy[k]][gx+sx[k]] == cn) return i;
      }
    }
  }
}


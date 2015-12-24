#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE   3  // 盤面の大きさ 3x3
#define STONE  3  // 目標連続石数

#define EMPTY  0  // 空白
#define BLACK  1  // 黒石
#define WHITE  2  // 白石

#define FIRST  1  // 先手
#define SECOND 2  // 後手

#define SUCC   1  // 着手可能
#define FAIL   0  // 着手不可能

#define WIN_F  1  // 先手勝利
#define WIN_S  2  // 後手勝利
#define FIN    3  // 引き分け:
#define CONT   0  // ゲーム続行

#define WIN    1  // 必勝局面
#define DRAW   0  // 引き分け
#define LOSE  -1  // 必敗局面

#define DEVELOPMENT  // コメントアウトされてなければ開発モード

#ifdef DEVELOPMENT  // 開発モードの処理定義
#define DEBUG printf  // DEBUG()をprintf()として処理
#else
#define DEBUG
#endif

typedef struct {
  int turn;  // 現在の手番
  int board[SIZE][SIZE];  // 現在の盤面
} PHASE;

void initialize(PHASE *p, int *humanTurn);
void finalize(PHASE *p, int status);

void init_board(PHASE *p);  // 盤面初期化
void print_board(PHASE *p);  // 盤面表示

void human(PHASE *p);  // 人間着手処理
void cpu(PHASE *p);  // AI着手処理

int check_move(PHASE *p, int x, int y);  // 入力座標の正誤確認
int check_end(PHASE *p);  // 終了判定
int check_five(PHASE *p, int x, int y);  // 石の連続確認

void change_phase(PHASE *p, int x, int y);  // 着手を行い局面を更新

int select_player_turn();  // 人間の手番選択


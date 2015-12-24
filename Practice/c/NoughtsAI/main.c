#include "noughts.h"

int main(int argc, char *argv[]) {
  int status;  // 局面状態
  int humanTurn;  // 先手後手確認用
  PHASE p;  // 局面管理

  srand((unsigned int)time(NULL));  // 乱数初期化

  initialize(&p, &humanTurn);  // 開始処理

  while (1) {
    if (p.turn == humanTurn) {  // 人間側着手
      human(&p);
    } else {  // AI側着手
      cpu(&p);
    }

    print_board(&p);  // 着手状態表示

    status = check_end(&p);  // 終了判定
    if (status != CONT) break;
  }

  finalize(&p, status);  // 終了処理

  return 0;
}


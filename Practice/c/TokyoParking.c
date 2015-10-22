#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
#define WIDTH 6
#define HEIGHT 6

// 1:縦向き  2:横向き
const int is_vert[MAX+1] = {-1, 0, 1, 0, 1};

// 車のサイズを確保
int car_length[MAX+1] = {0};

void init_board(int board[][WIDTH+2]) {
  int x, y;

  for (y=0; y<HEIGHT+2; y++) {
    for (x=0; x<WIDTH+2; x++) {
      if (x == 0 || x == 7) board[y][x] = -1;
      if (y == 0 || y == 7) board[y][x] = -1;
    }
  }

  board[3][7] = 0;  // 出口
  board[3][3] = 1;  // 目標
  board[3][4] = 1;  // 目標
  board[1][5] = 2;
  board[2][5] = 2;
  board[3][5] = 2;
  board[5][5] = 3;
  board[5][6] = 3;
  board[4][4] = 4;
  board[5][4] = 4;
}

void print_board(int board[][WIDTH+2]) {
  int x, y;

  printf("┌ ─ ─ ─ ─ ─ ─ ┐\n");
  for (y=1; y<HEIGHT+1; y++) {
    for (x=0; x<WIDTH+2; x++) {
      if (x == 7 && y == 3) {
        printf("   EXIT");
      }
      else if (x == 0 || x == 7) {
        x? printf(" │"): printf("│");
        continue;
      }
      switch (board[y][x]) {
        case 0:
          if (x != 7 || y != 3) printf(" .");
          break;
        case 1:
          printf(" ☆");
          break;
        case 2:
          printf(" ■");
          break;
        case 3:
          printf(" ▲");
          break;
        case 4:
          printf(" △");
          break;
        default:
          break;
      }
    }
    printf("\n");
  }
  printf("└ ─ ─ ─ ─ ─ ─ ┘\n");
}

int is_vertical(int car) {
  return is_vert[car];
}

int set_car_size(int board[][WIDTH+2]) {
  int x, y;

  for (y=1; y<HEIGHT+1; y++) {
    for (x=1; x<WIDTH+1; x++) {
      car_length[board[y][x]] += 1;
    }
  }
}

void change_board(int car, int op, int board[][WIDTH+2]) {
  int x, y;
  int setX = 0, setY = 0;  // 対象へ変更する座標
  int moveX = 0, moveY = 0;  // X, Y方向の移動量
  int clearX = 0, clearY = 0;  // 空き領域へ変更する座標

  if (is_vertical(car) == 0) {
    moveX = (op == 2)? 1: -1;
  } else if (is_vertical(car) == 1) {
    moveY = (op == 2)? 1: -1;
  }

  for (y=0; y<HEIGHT+2; y++) {
    for (x=0; x<WIDTH+2; x++) {
      if (board[y][x] == car) {
        if (board[y+moveY][x+moveX] == -1){
          fprintf(stderr, "[ERROR]  移動可能領域外へと移動しようとしています。\n");
          return;
        }
        if ((board[y+moveY][x+moveX] == 0 || board[y+moveY][x+moveX] == car) && board[y-moveY][x-moveX] != car) {
          clearX = x;
          clearY = y;
        }
        if ((board[y-moveY][x-moveX] == 0 || board[y-moveY][x-moveX] == car) && board[y+moveY][x+moveX] == 0) {
          setX = x+moveX;
          setY = y+moveY;
        }
      }
    }
  }

  board[setY][setX] = car;
  board[clearY][clearX] = 0;
}

int main() {
  int car, op;
  int board[HEIGHT+2][WIDTH+2] = {0};  // ゼロ初期化

  init_board(board);

  printf("☆ の車を出口まで動かしてください.\n");

  // メインループ
  while (1) {
    print_board(board);
    printf("どの車を動かしますか？ (☆ :1 ■ :2 ▲ :3 △ :4)  ");
    scanf("%d", &car);
    if (is_vertical(car)) {
      printf("どの方向に動かしますか？ (↑ :1 ↓ :2 キャンセル:0)  ");
    } else {
      printf("どの方向に動かしますか？ (← :1 → :2 キャンセル:0)  ");
    }
    scanf("%d", &op);
    if (op == 0) continue;
    change_board(car, op, board);
    if (board[3][7] == 1) break;
  }

  printf("\n駐車場を出ることに成功しました!!\n");

  return 0;
}


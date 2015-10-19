#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
#define WIDTH 6
#define HEIGHT 6

// 1:縦向き 0:横向き
const int is_vert[MAX+1] = {-1, 0, 1, 0, 1};

// Initialize
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

void change_board(int car, int op, int board[][WIDTH+2]) {
  int x, y, dic, flag = 0;
  int clearX, clearY;

  dic = (op == 1)? -1: 1;

  for (y=0; y<HEIGHT+2; y++) {
    for (x=0; x<WIDTH+2; x++) {
      if (is_vertical(car)) {
        if (board[y][x] == car) {
          if (board[y+dic][x] == -1) {
            fprintf(stderr, "移動可能領域外へ移動しようとしています。\n");
            return;
          }
          printf("flag:%d\n", flag);
          if (flag == 0) {
            printf("x:%d  y:%d\n", x, y);
            clearX = x;
            clearY = y;
            flag++;
          }
          board[y+dic][x] = car;
          print_board(board);
        }
      } else {
        if (board[y][x] == car) {
          if (board[y][x+dic] == -1) {
            fprintf(stderr, "移動可能領域外へ移動しようとしています。\n");
            return;
          }
          printf("flag:%d\n", flag);
          if (flag == 0) {
            printf("x:%d  y:%d\n", x, y);
            clearX = x;
            clearY = y;
            flag++;
          }
          board[y][x+dic] = car;
          print_board(board);
        }
      }
      printf("Y:%d  X:%d\n", clearY, clearX);
      board[clearY][clearX] = 0;
    }
  }
}

int main() {
  int car, op;
  int board[HEIGHT+2][WIDTH+2] = {0};

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
    if (board[3][7] == 2) break;
  }

  printf("駐車場を出ることに成功しました。\n");

  return 0;
}


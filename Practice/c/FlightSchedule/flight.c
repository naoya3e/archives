#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _FLIGHT {
  char carrier[10];  // 航空会社
  char from[10];     // 出発地
  char to[10];       // 到着地
  int num;           // 便名
  int d_hour;        // 出発時刻 hh
  int d_min;         // 出発時刻 mm
  int a_hour;        // 到着時刻 hh
  int a_min;         // 到着時刻 mm
} FLIGHT;

// フライトデータ全取得
int read_airline(char *files[], int n, FLIGHT airline[]) {
  int i, j = 0;
  char carrier[10];  // 航空会社
  char from[10];  // 出発地
  char to[10];  // 到着地
  FILE *fp;

  for (i=0; i<n; i++) {
    // ARGVは0番目に実行ファイル名が入っているので読み飛ばし
    if ((fp = fopen(files[i+1], "r")) == NULL) {
      fprintf(stderr, "ERROR: Cannot read file.\n");
      exit(EXIT_FAILURE);
    }

    fscanf(fp, "%s", carrier);  // ファイルから航空会社を読み取り
    fscanf(fp, "%s%s", from, to);  // ファイルから出発地と到着地を読み取り

    while (fscanf(fp, "%d,%d:%d,%d:%d", &airline[j].num, &airline[j].d_hour, &airline[j].d_min, &airline[j].a_hour, &airline[j].a_min) != EOF) {
      strcpy(airline[j].carrier, carrier);
      strcpy(airline[j].from, from);
      strcpy(airline[j].to, to);
      j++;
    }

    fclose(fp);
  }

  return j;
}

// 該当フライトデータ取得
FLIGHT *search_flight(FLIGHT airline[], int hour, int min, int dep, int arr) {
  int i;
  int status;  // 出発地と到着地の整合性状況
  int ref_time;  // 出発時刻を分単位へ変換
  int input_time;  // 入力時間を分単位へ変換
  int dif_time = 1500;  // 指定時間と出発時間の最近の差
  char departure[10];  // 引数に従って文字列変換
  char arrival[10];  // 引数に従って文字列変換
  FLIGHT *target = NULL;

  strcpy(departure, (dep == 1)? "岡山": "羽田");
  strcpy(arrival, (arr == 1)? "岡山": "羽田");

  input_time = 60*hour + min;

  for (i=0; i<airline[i].num!=0; i++) {
    ref_time = 60*airline[i].d_hour + airline[i].d_min;
    status = strcmp(airline[i].from, departure) || strcmp(airline[i].to, arrival);

    if (ref_time >= input_time && dif_time > ref_time - input_time && status == 0) {
      dif_time = ref_time - input_time;
      target = &airline[i];
    }
  }

  return target;
}

// 該当フライトデータ表示
void print_flight(FLIGHT *flight, int n) {
  if (flight == NULL) {
    if (n == 0) printf("フライトがありませんでした.\n");
  } else {
    printf("%2d.  %s %4d便 %s %02d:%02d発 %s %02d:%02d着\n", n+1, flight->carrier, flight->num, flight->from, flight->d_hour, flight->d_min, flight->to, flight->a_hour, flight->a_min);
  }
}

int main(int argc, char *argv[]) {
  int i;
  int flights;  // フライト数
  int hour, min;  // 指定時刻 hh:mm
  int dep, arr, n;  // 出発地, 到着地, 表示数
  FLIGHT *line;  // 該当フライト参照ポインタ
  FLIGHT airline[40] = {0};  // フライト数が40までなら格納できる

  flights = read_airline(argv, argc-1, airline);

  printf("時刻を(hh:mm)の形式で入力してください >> ");
  scanf("%d:%d", &hour, &min);
  printf("出発地を選んでください (1:岡山, 2:羽田) >> ");
  scanf("%d", &dep);
  printf("到着地を選んでください (1:岡山, 2:羽田) >> ");
  scanf("%d", &arr);
  printf("表示数を入力してください [1-10] >> ");
  scanf("%d", &n);

  if (dep == arr || n < 1 || n > 10) {
    fprintf(stderr, "ERROR: Unexpected value was inputted.\n");
    exit(EXIT_FAILURE);
  }

  for (i=0; i<n; i++) {
    line = search_flight(airline, hour, min, dep, arr);
    print_flight(line, i);
    if (line == NULL) break;
    hour = line->d_hour;
    min  = line->d_min  + 1;
  }

  return 0;
}


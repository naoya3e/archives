#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _FLIGHT {
  char carrier[10];  // 航空会社
  char from[10];     // 出発地
  char to[10];       // 到着地
  int num;           // 便名
  int d_hour;        // 出発時刻 時
  int d_min;         // 出発時刻 分
  int a_hour;        // 到着時刻 時
  int a_min;         // 到着時刻 分
} FLIGHT;

int read_airline(char *filename[], int n, FLIGHT airline[]) {
  int i = 0;
  char carrier[10];
  char from[10];
  char to[10];
  FILE *fp;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "ERROR: Cannot read file.\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%s", carrier);
  fscanf(fp, "%s%s", from, to);

  while (fscanf(fp, "%d,%d:%d,%d:%d", &airline[i].num, &airline[i].d_hour, &airline[i].d_min, &airline[i].a_hour, &airline[i].a_min) != EOF) {
    strcpy(airline[i].carrier, carrier);
    strcpy(airline[i].from, from);
    strcpy(airline[i].to, to);
    i++;
  }

  fclose(fp);

  return i;
}

FLIGHT *search_flight(FLIGHT airline[], int hour, int min) {
  int i = 0;
  int dif_hour = 24, dif_min = 60;
  int rel_hour, rel_min;
  FLIGHT *target = NULL;

  for (i=0; i<sizeof(airline)-2; i++) {
    printf("now_hour:%d  now_min:%d\n", airline[i].d_hour, airline[i].d_min);
    rel_hour = airline[i].d_hour - hour;
    rel_min  = airline[i].d_min - min;

    if (rel_hour >= 0 && rel_min >= 0 && dif_hour > rel_hour && dif_min > rel_min) {
      dif_hour = rel_hour;
      dif_min = rel_min;
      target = &airline[i];
    }
  }

  return target;
}

void print_flight(FLIGHT *flight) {
  if (flight == NULL) {
    printf("フライトがありませんでした.\n");
  } else {
    printf("%s%4d便 %s %02d:%02d発 %s %02d:%02d着\n", flight->carrier, flight->num, flight->from, flight->d_hour, flight->d_min, flight->to, flight->a_hour, flight->a_min);
  }
}

int main(int argc, char *argv[]) {
  int i;
  int flights;
  int hour, min;
  int dep, arr, n;
  char *files[10];
  FLIGHT airline[10];
  FLIGHT *line;

  for (i=0; i<argc; i++) {
    strcpy(files[i], argv[i+1]);
  }

  flights = read_airline(files, argc-1, airline);

  printf("時刻を(hh:mm)の形式で入力してください >> ");
  scanf("%d:%d", &hour, &min);
  printf("出発地を選んでください (1:岡山, 2:羽田) >> ");
  scanf("%d", &dep);
  printf("到着地を選んでください (1:岡山, 2:羽田) >> ");
  scanf("%d", &arr);
  printf("表示数を入力してください [1-10] >> ");
  scanf("%d", &n);

  if (dep != 1 || dep != 2 || arr != 1 || arr != 2 || n < 1 || n > 10) {
    fprintf(stderr, "ERROR: Unexpected value was inputted.");
    exit(EXIT_FAILURE);
  }

  line = search_flight(airline, hour, min);
  print_flight(line);

  return 0;
}


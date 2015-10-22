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

int read_airline(char filename[], FLIGHT airline[]) {
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

void print_airline(FLIGHT airline[], int n) {
  int i;

  printf("フライトスケジュールを表示します.\n");

  for (i=0; i<n; i++) {
    printf("%d.  %s%4d便 %02d:%02d →  %02d:%02d\n", i+1, airline[i].carrier, airline[i].num, airline[i].d_hour, airline[i].d_min, airline[i].a_hour, airline[i].a_min);
  }
}

FLIGHT *search_flight(FLIGHT airline[], int hour, int min) {
  int i = 0;
  FLIGHT *target = NULL;

  for (i=0; i<sizeof(airline)-2; i++) {  // 時刻は24時間表示のため、0<x<24について算術比較を行える
    if (airline[i].d_hour > hour && airline[i].d_min > min) {
      target = &airline[i];
      break;
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
  int flights;
  int hour, min;
  FLIGHT airline[10];
  FLIGHT *line;

  flights = read_airline(argv[1], airline);
  // print_airline(airline, flights);

  printf("時刻を(hh:mm)の形式で入力してください : ");
  scanf("%d:%d", &hour, &min);

  line = search_flight(airline, hour, min);
  print_flight(line);

  return 0;
}


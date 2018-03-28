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

FLIGHT *search_flight(FLIGHT airline[], int hour, int min) {
  int i;
  int ref_time;
  int input_time;
  int dif_time = 1500;
  FLIGHT *target = NULL;

  input_time = 60*hour + min;

  for (i=0; i<airline[i].num!=0; i++) {  // あんまり良くない気がするけど、フライト数とれないとこれしかない
    ref_time = 60*airline[i].d_hour + airline[i].d_min;

    if (ref_time >= input_time && dif_time > ref_time - input_time) {
      dif_time = ref_time - input_time;
      target = &airline[i];
    }
  }

  return target;
}

void print_flight(FLIGHT *flight) {
  if (flight == NULL) {
    printf("フライトがありませんでした.\n");
  } else {
    printf("%s%d便 %s %02d:%02d発 %s %02d:%02d着\n", flight->carrier, flight->num, flight->from, flight->d_hour, flight->d_min, flight->to, flight->a_hour, flight->a_min);
  }
}

int main(int argc, char *argv[]) {
  int flights;
  int hour, min;
  FLIGHT airline[10] = {0};
  FLIGHT *line;

  flights = read_airline(argv[1], airline);

  printf("時刻を(hh:mm)の形式で入力してください : ");
  scanf("%d:%d", &hour, &min);

  line = search_flight(airline, hour, min);
  print_flight(line);

  return 0;
}


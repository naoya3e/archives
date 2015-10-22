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
    printf("%d.  %s%d便 %02d:%02d →  %02d:%02d\n", i+1, airline[i].carrier, airline[i].num, airline[i].d_hour, airline[i].d_min, airline[i].a_hour, airline[i].a_min);
  }
}

int main(int argc, char *argv[]) {
  int flights;
  FLIGHT airline[10];

  flights = read_airline(argv[1], airline);
  print_airline(airline, flights);

  return 0;
}


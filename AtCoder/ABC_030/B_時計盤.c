#include <stdio.h>
#include <math.h>

int main() {
  int n, m;
  double angleShort, angleLong, ans;

  scanf("%d%d", &n, &m);

  angleShort = (n%12)*30.0 + m*0.5;
  angleLong = m*6.0;

  ans = fabs(angleShort - angleLong);
  printf("%f\n", (ans < 180)? ans: 360-ans);

  return 0;
}


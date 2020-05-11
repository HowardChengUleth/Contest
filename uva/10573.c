/* @JUDGE_ID: 1102NT 10573 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double pi = acos(0)*2;
  int N;
  double r1, r2, t;
  char line[1024];

  scanf("%d\n", &N);
  while (N-- > 0) {
    fgets(line, 1024, stdin);
    if (sscanf(line, "%lf %lf", &r1, &r2) == 1) {
      t = r1;
      printf("%.4f\n", t*t*pi/8.0);
    } else {
      printf("%.4f\n", 2*r1*r2*pi);
    }
  }
  return 0;
}

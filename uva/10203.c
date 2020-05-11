/* @JUDGE_ID: 1102NT 10203 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double hypot(double, double);

int main(void)
{
  int cases, m;
  double x1, x2, y1, y2;
  char buffer[1024];
  double d;

  scanf("%d\n", &cases);
  while (cases-- > 0) {
    scanf("%lf %lf\n", &x1, &x2);
    d = 0.0;
    while (fgets(buffer, 1024, stdin) && buffer[0] != '\n') {
      sscanf(buffer, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
      d += hypot(x1-x2, y1-y2);
    }
    d /= 10000.0;
    m = floor(d * 60.0 + 0.5);
    printf("%u:%02u\n", m/60, m%60);
    
    if (cases) {
      printf("\n");
    }
  }

  return 0;
}

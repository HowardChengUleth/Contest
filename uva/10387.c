/* @JUDGE_ID: 1102NT 10387 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double hypot(double,double); /* not ansi, need this for UVA */

int main(void)
{
  int a, b, s, m, n;
  double angle, v, t;
  double pi = 3.14159265358979323846;

  while (scanf("%d %d %d %d %d", &a, &b, &s, &m, &n) == 5 &&
	 a || b || s || m || n) {
    if (n == 0) {
      angle = 0.0;
    } else if (m == 0) {
      angle = 90.0;
    } else {
      t = atan((double)n*b/((double)m*a));
      angle = 180.0*t/pi;
    }
    v = hypot((double)n*b, (double)m*a) / s;
    printf("%.2lf %.2lf\n", angle, v);
  }
  return 0;
}

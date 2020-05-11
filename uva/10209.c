/* @JUDGE_ID: 1102NT 10209 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double a;
  const double pi = atan(1)*4;
  const double r3 = 4 - (sqrt(3) + 2*pi/3);
  const double r1 = pi - (sqrt(3) + 2*pi/3) + 1;
  const double r2 = 1 - r1 - r3;

  while (scanf("%lf", &a) == 1) {
    printf("%.3f %.3f %.3f\n", r1*a*a, r2*a*a, r3*a*a);
  }
  return 0;
}

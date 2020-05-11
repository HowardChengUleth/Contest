/* @JUDGE_ID: 1102NT 10432 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double r, theta, h, b;
  double pi = atan(1)*4;
  int n;

  while (scanf("%lf %d", &r, &n) == 2) {
    theta = 2*pi/n;       /* angle of one triangular "slice" */
    b = sin(theta/2) * r * 2;
    h = cos(theta/2) * r;
    printf("%.3f\n", n*(b*h/2));
  }
  return 0;
}

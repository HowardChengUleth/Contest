/* @JUDGE_ID: 1102NT 10297 C "" */

#include <stdio.h>
#include <math.h>

int main(void)
{
  int D, v;
  double d, pi;

  pi = acos(-1);
  while (scanf("%d %d", &D, &v) == 2 && (D || v)) {
    d = pow(pow(D,3) - 6*v/pi, 1.0/3.0);
    printf("%.3f\n", d);
  }
  return 0;
}

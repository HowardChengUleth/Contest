/*
 * look for "Triangle Median" on Mathworld
 *
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double m1, m2, m3, sm, t, area;

  while (scanf("%lf %lf %lf", &m1, &m2, &m3) == 3) {
    sm = (m1+m2+m3)/2.0;
    t = sm * (sm-m1) * (sm-m2) * (sm-m3);
    if (t <= 0.0) {
      area = -1.0;
    } else {
      area = 4.0/3.0 * sqrt(t);
    }
    printf("%.3f\n", area);
  }
  return 0;

}

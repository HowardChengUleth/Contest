/* @JUDGE_ID: 1102NT 10221 C "" */

#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  const double r = 6440;
  double s, a;
  double pi = atan(1)*4;
  char unit[1024];
  double ad, cd;

  while (scanf("%lf %lf %s", &s, &a, unit) == 3) {
    if (strcmp(unit, "deg") == 0) {
      a *= pi/180.0;
    } else {
      a *= pi/(180.0*60);
    }
    if (a > pi) {
      a = 2*pi - a;     /* arc distance is not always CCW */
    }

    ad = (r+s)*a;
    cd = sqrt(2*(r+s)*(r+s) - 2*(r+s)*(r+s)*cos(a));
    printf("%.6f %.6f\n", ad, cd);
  }
  return 0;
}

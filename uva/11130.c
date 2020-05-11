#include <stdio.h>
#include <math.h>

int main(void)
{
  int a, b, v, A, s;
  double dist, vdist, hdist, angle;
  double pi = acos(-1);
  int htimes, vtimes;

  while (scanf("%d %d %d %d %d", &a, &b, &v, &A, &s) == 5 &&
	 (a || b || v || A || s)) {
    dist = v*s/2.0;
    angle = A*pi/180;
    vdist = sin(angle)*dist;
    hdist = cos(angle)*dist;
    htimes = vtimes = 0;
    if (vdist >= b/2.0) {
      htimes++;
      vdist -= b/2.0;
    }
    htimes += floor(vdist/b);

    if (hdist >= a/2.0) {
      vtimes++;
      hdist -= a/2.0;
    }
    vtimes += floor(hdist/a);

    printf("%d %d\n", vtimes, htimes);

  }
  return 0;
}

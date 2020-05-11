#include <stdio.h>
#include <math.h>

#define FEPS 1e-10
#define EPS 1e-8

int p, q, r, s, t, u;

double f(double x)
{
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main(void)
{

  while (scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) == 6) {
    /* f(x) is decreasing from 0 to 1 */
    double lo = 0;
    double hi = 1;
    double flo = f(lo), fhi = f(hi);
    double mid, fmid;

    if (fabs(flo) < FEPS) {
      printf("%.4f\n", lo);
      continue;
    } else if (fabs(fhi) < FEPS) {
      printf("%.4f\n", hi);
      continue;
    } else if (flo < 0 || fhi > 0) {
      printf("No solution\n");
      continue;
    }

    while (hi - lo > EPS) {
      mid = (lo + hi) / 2;
      fmid = f(mid);
      if (fmid == 0) {
	lo = hi = mid;
      } else if (fmid > 0) {
	lo = mid;
      } else {
	hi = mid;
      }
    }
    printf("%.4f\n", (lo+hi)/2);
  }

  return 0;
}

/* @JUDGE_ID: 1102NT 10668 C "" */
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EPS 1e-15
double evalf(double L, double Lprime, double alpha)
{
  return L / Lprime - sin(alpha) / alpha;
}

/* solve L/Lprime - sin(alpha)/alpha = 0 with bisection */
double find_alpha(double L, double Lprime)
{
  double pi = atan(1)*4;

  double lo = 0.0001, hi = pi/2;
  double mid;
  double f1, f2, f3;

  f1 = evalf(L, Lprime, lo);
  f3 = evalf(L, Lprime, hi);
  while (hi - lo >= EPS) {
    mid = (lo+hi)/2;
    f2 = evalf(L, Lprime, mid);
    if (fabs(f2) < EPS) {
      return mid;
    }

    if (f1*f2 < 0) {
      hi = mid;
      f3 = f2;
    } else if (f2*f3 < 0) {
      lo = mid;
      f1 = f2;
    } else {
      assert(0);
    }
  } 
  return (lo+hi)/2;
}

int main(void)
{
  double L, n, C, Lprime, alpha;
  double R;

  while (scanf("%lf %lf %lf", &L, &n, &C) == 3 &&
	 (L >= 0 && n >= 0 && C >= 0)) {
    Lprime = (1 + n*C)*L;

    if (fabs(Lprime-L) < EPS) {
      printf("%.3f\n", 0.0);
    } else {
      alpha = find_alpha(L, Lprime);
      R = L/2/sin(alpha);
      printf("%.3f\n", R - R*cos(alpha));
    }
  }


  return 0;
}

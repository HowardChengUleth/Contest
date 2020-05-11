/* @JUDGE_ID: 1102NT 10215 C "" */

#include <stdio.h>
#include <math.h>

#define EPS 1e-8

double volume(double L, double W, double x)
{
  return (L - 2*x)*(W - 2*x)*x;
}

int main(void)
{
  double L, W;
  double x1;
  double x[4], v[4];
  int i, j, n;

  while (scanf("%lf %lf", &L, &W) == 2) {
    n = 0;

    x1 = (L + W + sqrt(L*L - L*W + W*W))/6;
    if (0 < x1 && 2*x1 < L && 2*x1 < W) {
      x[n++] = x1;
    }
    x1 = (L + W - sqrt(L*L - L*W + W*W))/6;
    if (0 < x1 && 2*x1 < L && 2*x1 < W) {
      x[n++] = x1;
    }
    x[n++] = 0.0;
    x[n++] = (L < W) ? L/2.0 : W/2.0;
    
    for (i = 0; i < n; i++) {
      v[i] = volume(L, W, x[i]);
    }

    for (i = 0; i < n; i++) {
      for (j = 0; j < n-1; j++) {
	if (v[j] > v[j+1]) {
	  x1 = x[j]; x[j] = x[j+1]; x[j+1] = x1;
	  x1 = v[j]; v[j] = v[j+1]; v[j+1] = x1;
	}
      }
    }

    printf("%.3f", x[n-1]+EPS);
    for (i = 0; i < n && v[i] < 1e-8; i++) {
      printf(" %.3f", x[i]+EPS);
    }
    printf("\n");
  }
  return 0;
}

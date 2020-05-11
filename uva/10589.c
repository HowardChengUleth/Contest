#include <stdio.h>
#include <math.h>

int main(void)
{
  int M, N;
  double a;
  double x, y;
  double x_sq1, x_sq2, y_sq1, y_sq2;
  int i;

  while (scanf("%d %lf", &N, &a) == 2 && N) {
    M = 0;
    for (i = 0; i < N; i++) {
      scanf("%lf %lf", &x, &y);
      x_sq1 = x*x;
      y_sq1 = y*y;
      x_sq2 = (a-x)*(a-x);
      y_sq2 = (a-y)*(a-y);
      if (x_sq1+y_sq1 <= a*a && x_sq2+y_sq1 <= a*a &&
	  x_sq1+y_sq2 <= a*a && x_sq2+y_sq2 <= a*a) {
	M++;
      }
    }
    printf("%.5f\n", M*a*a/N);
  }
  return 0;
}

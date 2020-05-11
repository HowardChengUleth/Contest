#include <stdio.h>
#include <math.h>

int main(void)
{
  double n;
  double a, dx;

  while (scanf("%lf", &n) == 1 && n > 1e-8) {
    a = floor(pow(n, 1/3.0));
    while ((a+1)*(a+1)*(a+1) <= n) {
      a++;
    }
    dx = (n - a*a*a)/(3*a*a);
    printf("%.4f\n", a+dx);
  }
  return 0;
}

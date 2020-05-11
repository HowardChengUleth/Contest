#include <stdio.h>
#include <math.h>

int main(void)
{
  double A, r, Pi;
  int n;
  int cases = 1;

  Pi = 2*acos(0);
  while (scanf("%d %lf", &n, &A) == 2 && n >= 3) {
    r = sqrt(A/n/cos(Pi/n)/sin(Pi/n));
    printf("Case %d: %.5f %.5f\n", cases++, r*r*Pi - A, 
	   A - r*r*cos(Pi/n)*cos(Pi/n)*Pi); 
  }

  return 0;
}

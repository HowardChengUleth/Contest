#include <stdio.h>
#include <math.h>

int main(void)
{
  double pi = acos(-1.0);
  double F, x;

  /* look at the triangle formed by one side of the pentagon and the top
     side of the square, apply sine law */
  while (scanf("%lf", &F) == 1) {
    x = F * sin(108*pi/180) / sin(63*pi/180);
    printf("%.10lf\n", x);
  }
  return 0;
}

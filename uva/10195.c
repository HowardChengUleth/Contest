/*
 * This is the "incircle" and "inradius".  Look that up.
 *
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double a, b, c, r;

  while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
    if (a*b*c == 0.0) {
      r = 0.0;
    } else {
      r = 0.5 * sqrt((b+c-a)*(c+a-b)*(a+b-c)/(a+b+c));
    }
    
    printf("The radius of the round table is: %.3f\n", r);
  }

  return 0;
}

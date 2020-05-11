#include <stdio.h>
#include <math.h>


/* the two pillars are the foci of an ellipse.  The area of an ellipse is
   PI * a * b where a and b are the major and minor axes. */

int main(void)
{
  int N;
  double D, L, area, a, b;
  const double PI = 2*acos(0);
 
  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%lf %lf", &D, &L);
    a = L/2.0;
    b = sqrt(L*L/4.0 - D*D/4.0);
    area = PI * a * b;
    printf("%.3f\n", area);

  }

  return 0;
}

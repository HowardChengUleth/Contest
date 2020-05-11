#include <stdio.h>
#include <math.h>

/*
 * Each car takes up (L+d) m on the road.  Therefore, it takes 
 * (L+d)/v s for each car to pass.  Hence, the volume is 3600s * v / (L+d).
 * Substitute d = v^2/(2f) and minimize volume by calculus gives 
 * v = sqrt(L*2*f).
 *
 */

int main(void)
{
  int L, f;
  double v, vol;

  while (scanf("%d %d", &L, &f) == 2 && (L || f)) {
    v = sqrt(L*2*f);
    vol = 3600*v / (L + v*v/(2*f));
    printf("%.8f %.8f\n", v, vol);
  }
    

  return 0;
}

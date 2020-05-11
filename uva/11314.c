#include <stdio.h>
#include <math.h>

int main(void)
{
  int n;
  double ax, ay, bx, by;
  
  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
    printf("%.3f\n", sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by)) +
	   sqrt((ax+bx)*(ax+bx)+(ay+by)*(ay+by)));
  }
  return 0;

}

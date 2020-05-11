/* @JUDGE_ID: 1102NT 256 C "" */

#include <stdio.h>
#include <math.h>

int power(int k)
{
  int x = 1;

  while (k-- > 0) {
    x *= 10;
  }
  return x;
}

int main(void)
{
  int n;
  int x, y1, y2;
  int a, b, c, d, r;
  char* fmt[5] = { "", "%d%d\n", "%02d%02d\n", "%03d%03d\n", "%04d%04d\n" };
  
  while (scanf("%d", &n) == 1) {
    for (x = 0; x < power(n/2); x++) {
      /* solve y^2 + (2x-1)y + (x^2-100x) = 0 */
      a = 1;
      b = 2*x-1;
      c = x*x - power(n/2)*x;
      
      d = b*b-4*a*c;
      r = sqrt(d);
      if (r*r != d && (r+1)*(r+1) != d) {
	continue;
      }
      if ((r+1)*(r+1) == d) {
	r++;
      }
      y1 = -b - r;
      y2 = -b + r;
      if (0 <= y1 && y1 < 2*power(n/2) && y1 % 2 == 0) {
	printf(fmt[n/2], x, y1/2);
      }
      if (0 <= y2 && y2 < 2*power(n/2) && y2 % 2 == 0) {
	printf(fmt[n/2], x, y2/2);
      }
    }
  }
  return 0;
}

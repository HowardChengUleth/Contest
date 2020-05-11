#include <stdio.h>
#include <math.h>

int main(void)
{
  int n;
  int b;
  int val, temp, mul, r, max_d, d;

  while (scanf("%d", &n) == 1 && n) {
    for (b = 2; b < 100; b++) {
      val = 0;
      temp = n;
      mul = 1;
      max_d = 0;
      while (temp > 0) {
	d = temp % 10;
	if (d > max_d) max_d = d;
	val += d * mul;
	temp /= 10;
	mul *= b;
      }
      if (max_d >= b) continue;

      r = (int)(floor(sqrt(val)) + 0.5);
      if (r*r == val || (r+1)*(r+1) == val) {
	printf("%d\n", b);
	break;
      }
    }
  }
  return 0;
}

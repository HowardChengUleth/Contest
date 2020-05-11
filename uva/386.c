/* @JUDGE_ID: 1102NT 386 C "" */

#include <stdio.h>

int main(void)
{
  long long a, b, c, d;
  long long a3, b3, c3, d3;

  for (a = 1; a <= 200; a++) {
    a3 = a*a*a;
    for (b = 2; b < a; b++) {
      b3 = b*b*b;
      for (c = b+1; c < a; c++) {
	c3 = c*c*c;
	if (b3+c3 > a3) break;
	for (d = c+1; d < a; d++) {
	  d3 = d*d*d;
	  if (a3 < b3+c3+d3) break;
	  if (a3 == b3+c3+d3) {
	    printf("Cube = %lld, Triple = (%lld,%lld,%lld)\n", a, b, c, d);
	  }
	}
      }
    }
  }

  return 0;
}

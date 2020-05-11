/* @JUDGE_ID: 1102NT 106 C "Brute force" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* all pythagorean triples are given by the following:

  x = a^2 - b^2
  y = 2ab
  z = a^2 + b^2

  where a > b

  so we just search for m, n up to sqrt(MAX)

*/

int gcd(int a, int b);
void process(int n);

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1) {
    process(n);
  }
  return 0;
}

int gcd(int a, int b)
{
  int r1, r2, r3;
  if (a < b) {
    return gcd(b, a);
  }

  r1 = a, r2 = b;
  while (r2 != 0) {
    r3 = r1 % r2;
    r1 = r2;
    r2 = r3;
  }
  return r1;
}

void process(int n)
{
  int x, y, z;
  int xx, yy, zz;
  int a, b;
  int i;
  int count1 = 0, count2 = 0;
  char used[1000001];

  for (i = 1; i <= n; i++) {
    used[i] = 0;
  }

  for (a = 1; a*a <= n; a++) {
    for (b = 1; b < a; b++) {
      if (gcd(a,b) > 1 || (a % 2 == b % 2)) {
	continue;
      }
      x = a*a - b*b;
      y = 2*a*b;
      z = a*a + b*b;
      if (z <= n) {
	if (gcd(x, gcd(y, z)) == 1) {
	  count1++;
	}
	xx = x;
	yy = y;
	zz = z;
	while (zz <= n) {
	  used[xx] = used[yy] = used[zz] = 1;
	  xx += x;
	  yy += y;
	  zz += z;
	}
      }     
    }
  }
  
  for (i = 1; i <= n; i++) {
    if (!used[i]) {
      count2++;
    }
  }

  printf("%d %d\n", count1, count2);
}

/* @JUDGE_ID: 1102NT 10717 C "" */

#include <stdio.h>
#include <limits.h>

int gcd(int a, int b)
{
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int lcm(int a, int b)
{
  int g = gcd(a,b);
  return (a/g) * b;
}

int lcm4(int a, int b, int c, int d)
{
  return lcm(lcm(a,b),lcm(c,d));
}

int main(void)
{
  int n, t, c[50];
  int i, table;
  int i1, i2, i3, i4, mult[250000], num_mult;
  int t1, t2;
  int best1, best2;

  while (scanf("%d %d", &n, &t) == 2 && (n || t)) {
    for (i = 0; i < n; i++) {
      scanf("%d", c+i);
    }

    num_mult = 0;
    for (i1 = 0; i1 < n; i1++) for (i2 = i1+1; i2 < n; i2++)
	for (i3 = i2+1; i3 < n; i3++) for (i4 = i3+1; i4 < n; i4++) {
	  mult[num_mult++] = lcm4(c[i1], c[i2], c[i3], c[i4]);
	}

    while (t-- > 0) {
      scanf("%d", &table);
      best1 = -1;
      best2 = INT_MAX;
      for (i = 0; i < num_mult; i++) {
	t1 = table - (table % mult[i]);
	t2 = table + (mult[i] - table % mult[i]) % mult[i];
	if (t1 > best1) {
	  best1 = t1;
	}
	if (t2 < best2) {
	  best2 = t2;
	}
      }
      printf("%d %d\n", best1, best2);
    }
  }

  return 0;
}

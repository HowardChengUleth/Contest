/* @JUDGE_ID: 1102NT 10407 C "" */

/* NOTE: it's actually enough to sort the integers and compute the GCD of
 *       the adjacent differences.  This is because the other differences
 *       are sums of the adjacent differences.
 */

/*
 * Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd.
 *
 */

#include <stdio.h>
#include <assert.h>


int gcd(int a, int b)
{
  int r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

int main(void)
{
  int num[1000];
  int n, x, d, i, j;

  while (scanf("%d", &x) == 1 && x) {
    n = 0;
    while (x) {
      num[n++] = x;
      scanf("%d", &x);
    }
    d = 0;
    for (i = 0; i < n; i++) {
      for (j = i+1; j < n; j++) {
	d = gcd(num[i]-num[j], d);
      }
    }
    printf("%d\n", d);
  }

  return 0;
}


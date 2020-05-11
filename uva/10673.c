/*
 * Extended Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd and the cofactors to form the
 * gcd as a linear combination.
 *
 * a*s + b*t = gcd(a,b)
 *
 */

#include <stdio.h>
#include <assert.h>

long long gcd(long long a, long long b, long long *s, long long *t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }

  *s = a1;
  *t = a2;
  return a;
}

int main(void)
{
  int T, x, k;
  long long g, s, t;

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &x, &k);
    if (x % k == 0) {
      printf("0 %d\n", k); 
    } else {
      g = gcd(x/k, x/k + 1, &s, &t);
      printf("%lld %lld\n", s*x, t*x);
    }

  }
  return 0;
}

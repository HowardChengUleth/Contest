/* @JUDGE_ID: 1102NT 10622 C "" */

#include <stdio.h>

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

long long power(long long n)
{
  long long g = 0;
  long long k, p;
  char neg = (n < 0);

  if (neg) {
    n *= -1;
  }
  k = 0;
  while (n % 2 == 0) {
    n /= 2;
    k++;
  }
  g = gcd(g, k);
  for (p = 3; p*p <= n; p += 2) {
    k = 0;
    while (n % p == 0) {
      n /= p;
      k++;
    }
    g = gcd(g, k);
  }
  if (n > 1) {
    g = 1;
  }

  if (!neg) {
    return g;
  } else {
    while (g % 2 == 0) {
      g /= 2;
    }
    return g;
  }
}

int main(void)
{
  long long n;

  while (scanf("%lld", &n) == 1 && n != 0) {
    printf("%lld\n", power(n));
  }
  return 0;
}

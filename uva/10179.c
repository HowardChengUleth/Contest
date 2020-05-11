/* @JUDGE_ID: 1102NT 10179 C "" */

#include <stdio.h>

int fast_exp(int b, int n)
{
  int res = 1;
  int x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
    } else {
      n >>= 1;
      x *= x;
    }
  }

  return res;
}

int phi(int n)
{
  int val = 1;
  int exp, p;

  exp = 0;
  p = 2;
  while (n % p == 0) {
    n /= p;
    exp++;
  }
  if (exp > 0) {
    val *= fast_exp(p, exp-1)*(p-1);
  }
  
  for (p = 3; p*p <= n; p += 2) {
    exp = 0;
    while (n % p == 0) {
      n /= p;
      exp++;
    }
    if (exp > 0) {
      val *= fast_exp(p, exp-1)*(p-1);
    }
  }

  if (n > 1) {
    val *= (n-1);
  }
  return val;
}

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1 && n > 0) {
    printf("%d\n", phi(n));
  }
  return 0;
}

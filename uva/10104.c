/* @JUDGE_ID: 1102NT 10104 C "" */

#include <stdio.h>
#include <assert.h>

int gcd(int a, int b, int *s, int *t)
{
  int r, r1, r2, a1, a2, b1, b2, q;
  int A = a;
  int B = b;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    r = gcd(-a, b, s, t);
    *s *= -1;
    return r;
  }
  if (b < 0) {
    r = gcd(a, -b, s, t);
    *t *= -1;
    return r;
  }

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    assert(a1*A + a2*B == a);
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
  assert(a >= 0);
  return a;
}

int main(void)
{
  int a, b, x, y, d;

  while (scanf("%d %d", &a, &b) == 2) {
    d = gcd(a, b, &x, &y);
    printf("%d %d %d\n", x, y, d);
  }
  return 0;
}

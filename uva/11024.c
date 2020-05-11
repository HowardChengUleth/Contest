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
  int N;
  int p11, p12, p21, p22, p, s11, s12, s21, s22;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d %d %d %d", &s11, &s12, &p11, &p12);
    scanf("%d %d %d %d", &s21, &s22, &p21, &p22);
    p = gcd(gcd(p11, p12), gcd(p21, p22));
    printf("%s\n", ((s21 - s11 - s22 + s12) % p == 0) ? "Yes" : "No");
    
  }

  return 0;
}

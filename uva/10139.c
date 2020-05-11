/* @JUDGE_ID: 1102NT 10139 C "" */

#include <stdio.h>
#include <math.h>

int divide(int n, int m)
{
  int d, e, denom, l;

  if (m == 0) {
    return 0;
  }
  
  e = 0;
  while (m % 2 == 0) {
    m /= 2;
    e++;
  }
  denom = 2;
  while (e > 0 && n / denom > 0) {
    e -= n / denom;
    denom *= 2;
  }
  if (e > 0) {
    return 0;
  }

  l = sqrt(m)+1;
  for (d = 3; d <= l; d += 2) {
    e = 0;
    while (m % d == 0) {
      m /= d;
      e++;
    }
    if (e) {
      l = sqrt(m)+1;
    }
    denom = d;
    while (e > 0 && n / denom > 0) {
      e -= n / denom;
      denom *= d;
    }
    if (e > 0) {
      return 0;
    }
  }
  if (m > 1 && m > n) {
    return 0;
  } else {
    return 1;
  }
}

int main(void)
{
  int n, m;

  while (scanf("%d %d", &n, &m) == 2) {
    if (divide(n, m)) {
      printf("%d divides %d!\n", m, n);
    } else {
      printf("%d does not divide %d!\n", m, n);
    }
  }
  return 0;
}

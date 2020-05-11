#include <stdio.h>

int isprime(int n) {
  long long p;

  if (n % 2 == 0) {
    return 0;
  }

  for (p = 3; p*p <= n; p += 2) {
    if (n % p == 0) 
      return 0;
  }
  return 1;
}

#include <stdio.h>
#include <assert.h>

int fast_exp(int b, int n, int m)
{
  long long res = 1;
  long long x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  return res;
}

int main(void) {
  int p, a;

  while (scanf("%d %d", &p, &a) == 2 && p && a) {
    if (!isprime(p) && fast_exp(a, p, p) == a) {
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }
  return 0;
}











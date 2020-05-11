#include <stdio.h>

/* note: when 2^p-1 is prime, 2^(p-1) * (2^p - 1) is always perfect. */

int isprime(long long n)
{
  long long k;

  if (n > 2 && n % 2 == 0) return 0;
  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) return 0;
  }
  return 1;
}

int main(void)
{
  long long result;
  int n;

  while (scanf("%d", &n) == 1 && n) {
    if (isprime((1LL << n) - 1)) {
      result = (1LL << (n-1)) * ((1LL << n) - 1);
      printf("Perfect: %lld!\n", result);
    } else if (isprime(n)) {
      printf("Given number is prime. But, NO perfect number is available.\n");
    } else {
      printf("Given number is NOT prime! NO perfect number is available.\n");
    }
  }
  return 0;
}

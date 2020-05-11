/* @JUDGE_ID: 1102NT 686 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRIME 32768

char primes[MAX_PRIME];

int isprime(int n)
{
  int i;
  
  if (n % 2 == 0) {
    return 0;
  }
  for (i = 3; i*i <= n; i += 2) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

void build_primes(void)
{
  int i;

  memset(primes, MAX_PRIME, 0);
  primes[2] = 1;
  for (i = 3; i < MAX_PRIME; i += 2) {
    if (isprime(i)) {
      primes[i] = 1;
    }
  }
}

int main(void)
{
  int n, count, i;

  build_primes();
  while (scanf("%d", &n) == 1 && n > 0) {
    count = 0;
    for (i = 2; i <= n/2; i++) {
      if (primes[i] && primes[n-i]) {
	count++;
      }
    }
    printf("%d\n", count);

  }
  return 0;
}

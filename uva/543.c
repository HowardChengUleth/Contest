#include <stdio.h>

int isprime(int n)
{
  int k;

  if (n == 1) {
    return 0;
  } else if (n == 2) {
    return 1;
  } else if (n % 2 == 0) {
    return 0;
  }
  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) {
      return 0;
    }
  }
  return 1;
}

char prime[1000000];

int main(void)
{
  int n, a;

  for (n = 1; n < 1000000; n++) {
    prime[n] = isprime(n);
  }

  while (scanf("%d", &n) == 1 && n) {
    for (a = 2; a <= n/2; a++) {
      if (prime[a] && prime[n-a]) {
	printf("%d = %d + %d\n", n, a, n-a);
	break;
      }
    }
    if (a > n/2) {
      printf("Goldbach's conjecture is wrong.\n");
    }
  }
  return 0;
}

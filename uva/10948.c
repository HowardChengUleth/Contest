#include <stdio.h>

char isprime[1000001];

void sieve(void)
{
  int i, k;

  for (i = 0; i <= 1000000; i++) {
    isprime[i] = 1;
  }
  isprime[0] = isprime[1] = 0;

  for (k = 2; k <= 1000000; k++) {
    if (!isprime[k]) continue;
    for (i = k+k; i <= 1000000; i += k) {
      isprime[i] = 0;
    }
  }
}

int main(void)
{
  int n, i;

  sieve();

  while (scanf("%d", &n) == 1 && n) {
    printf("%d:\n", n);
    for (i = 2; i <= n/2; i++) {
      if (isprime[i] && isprime[n-i]) {
	printf("%d+%d\n", i, n-i);
	break;
      }
    }
    if (i > n/2) {
      printf("NO WAY!\n");
    }
  }
  return 0;
}

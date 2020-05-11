#include <stdio.h>
#include <assert.h>

int isprime(int n)
{
  int k;

  /* n is guaranteed to be odd */
  if (n == 1) return 0;

  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) {
      return 0;
    }
  }

  return 1;
}

int main(void)
{
  int N, p;

  while (scanf("%d", &N) == 1) {
    if (N < 8) {
      printf("Impossible.\n");
      continue;
    }

    if (N % 2) {
      printf("2 3 ");
      N -= 5;
    } else {
      printf("2 2 ");
      N -= 4;
    }

    /* every even number can be expressed as a sum of two primes */
    if (N == 4) {
      printf("2 2\n");
      continue;
    }

    for (p = 3; p <= N/2; p += 2) {
      if (isprime(p) && isprime(N-p)) {
	printf("%d %d\n", p, N-p);
	break;
      }
    }
    assert(p <= N/2);
  }


  return 0;
}

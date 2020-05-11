/* @JUDGE_ID: 1102NT 10394 C "" */

#include <stdio.h>
#include <math.h>

char bitmap[20000000/8];   /* bit = 0 ==> prime, bit = 1 ==> not prime */

int twin_primes[100000];

#define GET_BIT(x) (bitmap[((x) >> 3)] & (1 << ((x) & 7)))
#define SET_BIT(x) bitmap[((x) >> 3)] |= (1 << ((x) & 7))

void sieve(void)
{
  int i, k;

  SET_BIT(0);
  SET_BIT(1);
  for (i = 2; i <= 5000; i++) {
    if (GET_BIT(i) == 0) {
      for (k = i+i; k <= 20000000; k += i) {
	SET_BIT(k);
      }
    }
  }
}

void init_twinprimes(void)
{
  int count = 0;
  int i;

  i = 3;
  while (count < 100000) {
    if (!(GET_BIT(i) || GET_BIT(i+2))) {
      twin_primes[count++] = i;
    }
    i += 2;
  }
}

int main(void)
{
  int k;

  sieve();
  init_twinprimes();
  while (scanf("%d", &k) == 1) {
    printf("(%d, %d)\n", twin_primes[k-1], twin_primes[k-1]+2);
  }
  return 0;
}

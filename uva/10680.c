/* @JUDGE_ID: 1102NT 10680 C "" */

/*
 * Idea: looking at the prime factorizations of 1, 2, ..., n, we see
 * that the only time when the LCM changes from 1, ..., n to 1, ..., n+1
 * is if n+1 is a power of a prime.
 *
 * So what we do is to precompute this in a table.
 *
 */

#include <stdio.h>

int primes[100000];
int num_primes;
char bitmap[1000001];

char answer[1000001];
int power_p[1000001];
char power_e[1000001];

/*
 * Do a sieve to initialize the primes array.  The primes array contains
 * all the prime numbers up to 1000000, with num_primes being the number of
 * elements in the array.
 *
 */
void init_primes(void)
{
  int i, k;
  
  primes[num_primes++] = 2;
  primes[num_primes++] = 3;

  /* in every group of 6, we only need to look at the ones that are
     1, 5 mod 6 */
  for (i = 5; i <= 1000000; i += 6) {
    if (!bitmap[i]) {
      primes[num_primes++] = i;
      for (k = 2*i; k <= 1000000; k += i) {
	bitmap[k] = 1;
      }
    }
    if (i+2 <= 1000000 && !bitmap[i+2]) {
      primes[num_primes++] = i+2;
      for (k = 2*i+4; k <= 1000000; k += i+2) {
	bitmap[k] = 1;
      }
    }
  }
}

/* computes the large power k such that 2^k <= n */
int largest_power2(int n)
{
  int k = 0, x = 2;

  while (x <= n) {
    x <<= 1;
    k++;
  }
  return k;
}

/* do the tricky precomputations.
 *
 * In order to find the last non-zero digit, we look at the powers of
 * 2 and 5.  An equal number of 2's and 5's gives powers of 10, so we
 * want to take them out.  Once the powers of 10 are removed, all we
 * have to do is to multiply the remaining numbers modulo 10 to get
 * the last non-zero digit.
 *
 * We will do this incrementally from 1 to 1000000.
 *
 */
void precompute(void)
{
  int i, p, e, t;

  init_primes();

  /* for each number[i], we want power_p[i] to be set to the p if i is a
     power of a prime p (and 0 otherwise).  power_e[i] would contain
     the exponent.  In other words, if i = p^k for some prime p,
     then power_p[i] = p and power_e[i] = k.
  */
  for (i = 0; i < num_primes; i++) {
    p = 1;
    e = 0;
    while (p <= 1000000 / primes[i]) {
      p *= primes[i];
      power_p[p] = primes[i];
      power_e[p] = ++e;
    }
  }

  t = 1;        /* t is the mod 10 product of all primes except 2 and 5 */
  answer[1] = 1;
  for (i = 2; i <= 1000000; i++) {
    if (!power_p[i]) {
      /* if i is not a prime power, the answer doesn't change */
      answer[i] = answer[i-1];
    } else {
      if (power_p[i] != 2 && power_p[i] != 5) {
	/* if p is not either 2 or 5, then we can just update t */
	t = (t * power_p[i]) % 10;
      }

      /* Notice that the powers of 2 accumulated so far is always
	 at least as many as the powers of 5 because 2 is smaller
	 so there are more of them.  So the only time we will have
	 more powers of 10 is when we see more 5's.
      */
      if (power_p[i] != 5) {
	/* no more power of 10's, so it is easy even if it is 2 */
	answer[i] = (answer[i-1] * power_p[i]) % 10;
      } else {
	/* now we have more trailing zeros because of extra 5's */

	/* first we assume that there are no 2's and 5's */
	answer[i] = t;
	
	/* now we have to put in the "leftover" 2's after 5's are
	   matched (to remove power of 10's).  The total number of
	   2's up to this point is the largest power of 2 that is no
           larger than i.  */
	e = largest_power2(i) - power_e[i];
	while (e-- > 0) {
	  answer[i] = (answer[i] << 1) % 10;
	}
      }
    }
  }
}

/* do all the computations in advance and just look up the answers */
int main(void)
{
  int N;

  precompute();
  while (scanf("%d", &N) == 1 && N > 0) {
    printf("%d\n", answer[N]);
  }
  return 0;
}

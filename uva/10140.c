#include <stdio.h>

int L, U;
char sieve[1000001];
int primes[1000000];
int num_primes;

void gen_primes(void)
{
  int i, k;

  for (i = 2; i <= 1000000; i++) {
    sieve[i] = 1;
  }

  for (k = 2; k <= 1000000; k++) {
    if (!sieve[k]) continue;
    for (i = 2*k; i <= 1000000; i += k) 
      sieve[i] = 0;
  }

  num_primes = 0;
  for (k = 2; k <= 1000000; k++) {
    if (sieve[k]) {
      primes[num_primes++] = k;
    }
  }
}

int isprime(int n)
{
  long long p;

  if (n == 1) return 0;
  if (n <= primes[num_primes-1]) return 1;
  for (p = primes[num_primes-1]+2; p*p <= n; p += 2) {
    if (n % p == 0) return 0;
  }
  return 1;
}

int main(void)
{
  int p, k;
  unsigned int start;
  unsigned int max_dist;
  int max_1, max_2;
  int min_dist;
  int min_1, min_2;
  int last_prime;
  int dist;
  int found;

  gen_primes();

  while (scanf("%d %d", &L, &U) == 2) {
    for (k = 0; k <= U-L; k++) {
      sieve[k] = 1;
    }
    
    for (p = 0; p < num_primes; p++) {
      if (L % primes[p] == 0) {
	start = L;
      } else {
	start = (unsigned int)L + (primes[p] - L % primes[p]);
      }
      while (start <= primes[p]) {
	start += primes[p];
      }

      start -= L;
      while (start <= U-L) {
	sieve[start] = 0;
	start += primes[p];
      }
    }

    for (k = 0; k <= U-L; k++) {
      if (!sieve[k]) continue;
      sieve[k] = isprime(k+L);
    }
    
    last_prime = -1;
    found = 0;
    for (k = 0; k <= U-L; k++) {
      if (sieve[k]) {
	if (last_prime >= 0) {
	  dist = k - last_prime;
	  if (!found || dist > max_dist) {
	    max_dist = dist;
	    max_1 = last_prime;
	    max_2 = k;
	  }
	  if (!found || dist < min_dist) {
	    min_dist = dist;
	    min_1 = last_prime;
	    min_2 = k;
	  }
	  found = 1;
	}
	last_prime = k;
      }
    }

    if (found) {
      printf("%d,%d are closest, %d,%d are most distant.\n",
	     min_1+L, min_2+L, max_1+L, max_2+L);
    } else {
      printf("There are no adjacent primes.\n");
    }
    
  }

  return 0;
}

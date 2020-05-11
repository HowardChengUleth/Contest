/* @JUDGE_ID: 1102NT 10533 C "" */

#include <stdio.h>
#include <stdlib.h>

int primes[80000];
int dprimes[80000];
int num_primes, num_dprimes;

int isprime(int n)
{
  int i;

  for (i = 0; i < num_primes && primes[i]*primes[i] <= n; i++) {
    if (n % primes[i] == 0) {
      return 0;
    }
  }
  return 1;
}

int isdprime(int n)
{
  int k = 0;
  
  while (n > 0) {
    k += n % 10;
    n /= 10;
  }
  return isprime(k);
}

void build_tables(void)
{
  int n;

  primes[num_primes++] = 2;
  dprimes[num_dprimes++] = 2;
  for (n = 3; n <= 1000000; n += 2) {
    if (isprime(n)) {
      primes[num_primes++] = n;
      if (isdprime(n)) {
	dprimes[num_dprimes++] = n;
      }
    }
  }
}

int bin_search(int *A, int n, int x, int *index)
{
   int l, u, m;

   if (n <= 0 || x < A[0]) {
      *index = 0;
      return 0;
   }
   if (A[n-1] < x) {
      *index = n;
      return 0;
   }
   if (x == A[n-1]) {
      *index = n-1;
      return 1;
   }
   l = 0;
   u = n-1;
   while (l+1 < u) {
      m = (l+u)/2;
      if (A[m] <= x) {
         l = m;
      } else {
         u = m;
      }
   }
   if (A[l] == x) {
      *index = l;
      return 1;
   } else {
      *index = u;
      return 0;
   }
}

int main(void)
{
  int N, t1, t2;
  int found, lo, hi;

  build_tables();
  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d %d", &t1, &t2);
    found = bin_search(dprimes, num_dprimes, t1, &lo);
    found = bin_search(dprimes, num_dprimes, t2, &hi);
    if (found) hi++;
    printf("%d\n", hi-lo);
  }
  return 0;
}

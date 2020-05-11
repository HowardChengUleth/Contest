/* @JUDGE_ID: 1102NT 10311 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int primes[10000];
int num_primes = 0;

int isprime(int n)
{
  int i;
  int s = floor(sqrt(n)+0.5);
  assert(n <= 100000000);
  for (i = 0; i < num_primes && primes[i] <= s; i++) {
    if (n % primes[i] == 0) {
      return 0;
    }
  }
  return 1;
}

void gen_primes(void)
{
  int i;

  primes[num_primes++] = 2;
  for (i = 3; i <= 10000; i += 2) {
    if (isprime(i)) {
      primes[num_primes++] = i;
    }
  }
}

void solve(int n)
{
  int k;

  if (n % 2) {
    if (n-2 >= 2 && isprime(n-2)) {
      printf("%d is the sum of %d and %d.\n", n, 2, n-2);
    } else {
      printf("%d is not the sum of two primes!\n", n);
    }
  } else {
    k = n/2;
    if (k % 2 == 0) {
      k--;
    }
    for (; k >= 3; k -= 2) {
      if (k != n-k && isprime(k) && isprime(n-k)) {
	assert(n-k > k);
	printf("%d is the sum of %d and %d.\n", n, k, n-k);
	break;
      }
    }
    if (k < 3) {
      printf("%d is not the sum of two primes!\n", n);
    }
  }

}

int main(void)
{
  int n;

  gen_primes();

  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}

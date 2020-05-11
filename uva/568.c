/* @JUDGE_ID: 1102NT 568 C "" */

/*
 * The idea:
 *
 * Compute the prime factorization of n!, remove as many powers of 10's
 * as necessary, and then do the computation mod 10.
 *
 */

#include <stdio.h>

int primes[10000];
int num_primes;

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

void init(void)
{
  int i;

  primes[num_primes++] = 2;
  for (i = 3; i <= 10000; i += 2) {
    if (isprime(i)) {
      primes[num_primes++] = i;
    }
  }
}

int find_power(int N, int p)
{
  int ans = 0, pp = p;
  
  while (N/pp > 0) {
    ans += N/pp;
    pp *= p;
  }
  return ans;
}

int powmod(int b, int k)
{
  int ans = 1;
  
  while (k-- > 0) {
    ans = (ans * b) % 10;
  }
  return ans;
}

int lastdigit(int N)
{
  int p2, p5;
  int p, i;
  int ans = 1;

  /* first find powers of 2, 5 */
  p2 = find_power(N,2);
  p5 = find_power(N,5);


  ans = (ans * powmod(2, p2-p5)) % 10;
  
  p = find_power(N,3);
  ans = (ans * powmod(3, p)) % 10;
  for (i = 3; i < num_primes; i++) {
    p = find_power(N, primes[i]);
    if (!p) break;
    ans = (ans * powmod(primes[i], p)) % 10;
  }
  return ans;
}

int main(void)
{
  int N;

  init();
  while (scanf("%d", &N) == 1) {
    printf("%5d -> %d\n", N, lastdigit(N));
  }
  return 0;
}

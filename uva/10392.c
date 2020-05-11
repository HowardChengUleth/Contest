/* @JUDGE_ID: 1102NT 10392 C "" */

#include <stdio.h>

#define PRIMES 100

long long primes[PRIMES] = {
  2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,
  103,107,109,113,127,131,137,139,149,151,157,163,167,173,179, 181, 191, 193,
  197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,
  311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,
  431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541
};

void factor(long long n)
{
  int i;
  long long d;
  int last;

  for (i = 0; i < PRIMES; i++) {
    while (n % primes[i] == 0) {
      n /= primes[i];
      printf("    %lld\n", primes[i]);
    }
  }

  d = primes[PRIMES-1]  + 2;
  last = d % 10;

  while (d*d <= n) {
    while (n % d == 0) {
      n /= d;
      printf("    %lld\n", d);
    }
    d += 2;
    last = (last + 2) % 10;
    if (last == 5) {
      d += 2;
      last = (last + 2) % 10;
    }
  }
  if (n > 1) {
    printf("    %lld\n", n);
  }
}

int main(void)
{
  long long n;

  while (scanf("%lld", &n) == 1 && n >= 0) {
    if (n <= 2) {
      printf("    %lld\n", n);
    } else {
      factor(n);
    }
    printf("\n");
  }
  return 0;
}

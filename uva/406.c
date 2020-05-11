#include <stdio.h>

int isprime(int N)
{
  int i;

  if (N == 1) return 1;   /* for this problem!!! */
  if (N == 2) return 1;
  if (N % 2 == 0) return 0;
  for (i = 3; i*i <= N; i += 2) {
    if (N % i == 0) {
      return 0;
    }
  }
  return 1;
}

int prime[1001];
int numprimes[1001];

void print_list(int skip, int len)
{
  int i;

  for (i = 1; i <= 1000; i++) {
    if (!prime[i]) continue;
    if (skip) {
      skip--;
    } else {
      printf(" %d", i);
      if (--len == 0) {
	return;
      }
    }
  }
}

int solve_case(void)
{
  int N, C, skip;
  
  if (scanf("%d %d", &N, &C) != 2) {
    return 0;
  }
  printf("%d %d:", N, C);

  if (numprimes[N] % 2 == 0) {
    if (C*2 > numprimes[N]) {
      C = numprimes[N]/2;
    }
    skip = numprimes[N]/2 - C;
    print_list(skip, 2*C);
  } else {
    if (C*2-1 > numprimes[N]) {
      C = (numprimes[N]+1)/2;
    }
    skip = (numprimes[N] - (C*2-1))/2;
    print_list(skip, 2*C-1);
  }
  printf("\n\n");
  return 1;
}

int main(void)
{
  int i;

  for (i = 1; i <= 1000; i++) {
    prime[i] = isprime(i);
  }
  numprimes[0] = 0;
  for (i = 1; i <= 1000; i++) {
    numprimes[i] = numprimes[i-1] + prime[i];
  }

  while (solve_case());


  return 0;
}

/* @JUDGE_ID: 1102NT 583 C "" */

#include <stdio.h>

void print_factor(long long n, char first)
{
  if (first) {
    printf(" %lld", n);
  } else {
    printf(" x %lld", n);
  }
}

void factor(long long n)
{
  char first = 1;
  long long k;

  printf("%lld =", n);
  if (n < 0) {
    print_factor(-1, first);
    n *= -1;
    first = 0;
  }

  while (n % 2 == 0) {
    n /= 2;
    print_factor(2, first);
    first = 0;
  }

  for (k = 3; k*k <= n; k += 2) {
    while (n % k == 0) {
      n /= k;
      print_factor(k, first);
      first = 0;
    }
  }
  
  if (first || n > 1) {
    print_factor(n, first);
  }
  printf("\n");
}

int main(void)
{
  long long n;

  while (scanf("%lld", &n) == 1 && n != 0) {
    factor(n);
  }
  return 0;
}

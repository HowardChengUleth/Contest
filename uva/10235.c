#include <stdio.h>


char isprime[1000001];
int reverse[1000001];

int rev(int n)
{
  int res = 0;

  while (n) {
    res *= 10;
    res += n % 10;
    n /= 10;
  }
  return res;
}

void init(void)
{
  int i, j;

  for (i = 2; i <= 1000000; i++) {
    isprime[i] = 1;
  }
  
  for (i = 2; i <= 1000000; i++) {
    if (!isprime[i]) continue;
    for (j = 2*i; j <= 1000000; j += i) {
      isprime[j] = 0;
    }
  }

  for (i = 0; i <= 1000000; i++) {
    reverse[i] = rev(i);
  }
}

int main(void)
{
  int N;

  init();
  
  while (scanf("%d", &N) == 1) {
    if (!isprime[N]) {
      printf("%d is not prime.\n", N);
    } else if (isprime[reverse[N]] && N != reverse[N]) {
      printf("%d is emirp.\n", N);
    } else {
      printf("%d is prime.\n", N);
    }
  }
  return 0;
}

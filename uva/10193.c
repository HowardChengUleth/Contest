#include <stdio.h>

long long read_num(void)
{
  char line[31];
  int i;
  long long n = 0;

  scanf("%s", line);
  for (i = 0; line[i]; i++) {
    n *= 2;
    n += line[i] - '0';
  }
  return n;
}

long long gcd(long long a, long long b)
{
  if (!b) {
    return a;
  }
  return gcd(b, a % b);
}

int main(void)
{
  int N;
  int i, num1, num2;

  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    num1 = read_num();
    num2 = read_num();
    printf("Pair #%d: ", i);
    if (gcd(num1, num2) == 1) {
      printf("Love is not all you need!\n");
    } else {
      printf("All you need is love!\n");
    }
  }
  return 0;
}
  

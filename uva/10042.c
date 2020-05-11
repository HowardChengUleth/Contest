/* @JUDGE_ID: 1102NT 10042 C "" */

#include <stdio.h>

long long sum_digits(long long n)
{
  long long sum = 0;

  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

int smith(long long n)
{
  long long sum1, sum2;
  long long fact;
  int prime = 1;
  
  sum1 = sum_digits(n);

  sum2 = 0;
  while (2*2 <= n && n % 2 == 0) {
    n /= 2;
    sum2 += 2;
    prime = 0;
  }
  fact = 3;
  while (fact*fact <= n) {
    while (n % fact == 0) {
      n /= fact;
      sum2 += sum_digits(fact);
      prime = 0;
    }
    fact += 2;
  }
  if (n > 1) {
    sum2 += sum_digits(n);
  }
  return (!prime && sum1 == sum2);
}

long long find_smith(long long n)
{
  while (1) {
    if (smith(++n)) {
      return n;
    }
  }
}

int main(void)
{
  int cases;
  long long n;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%lld", &n);
    printf("%lld\n", find_smith(n));
  }
  return 0;
}

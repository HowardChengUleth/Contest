/* @JUDGE_ID: 1102NT 10200 C "" */

#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
  int k;
  
  if (n % 2 == 0) {
    return 0;
  }
  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int a, b, i;
  char prime[10001];
  int count[10001];
  double result;

  for (i = 0; i < 40; i++) {
    prime[i] = 1;
    count[i] = i+1;
  }
  for (i = 40; i <= 10001; i++) {
    prime[i] = is_prime(i*i+i+41);
    count[i] = (i == 0) ? prime[i] : prime[i] + count[i-1];
  }
  while (scanf("%d %d", &a, &b) == 2) {
    if (a > 0) {
      result = (double)(count[b] - count[a-1]) * 100.0 / (b-a+1);
    } else {
      result = (double)count[b] * 100.0 / (b+1);
    }

    /* need to fudge a bit */
    result = floor(result*100+0.5+1e-8)/100.0;
    printf("%.2f\n", result);

  }
  return 0;
}

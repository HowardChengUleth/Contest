/* @JUDGE_ID: 1102NT 10219 C "" */

#include <stdio.h>
#include <math.h>

int choose(int long n, int k)
{
  int i;
  long double sum = 0.0;

  if (n == k || k == 0) {
    return 1;
  }

  for (i = n-k+1; i <= n; i++) {
    sum += log10(i);
  }
  for (i = 1; i <= k; i++) {
    sum -= log10(i);
  }
  if (sum < 0) {   /* guard against -0.00 */
    sum = 0;
  }
  return (int)(1 + floor(sum));
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int main(void)
{
  int n, k;
  
  while (scanf("%d %d", &n, &k) == 2) {
    printf("%d\n", choose(n, min(k, n-k)));
  }
  return 0;
}

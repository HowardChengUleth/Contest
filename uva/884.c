#include <stdio.h>

char composite[1000001];
int ans[1000001];

int factors(int n)
{
  int i;

  if (!composite[n]) return 1;
  if (n % 2 == 0) return 1 + factors(n/2);
  for (i = 3; i*i <= n; i += 2) {
    if (n % i == 0) return 1 + factors(n/i);
  }
  return 0;
}

int main(void)
{
  int n, i, j;

  composite[0] = composite[1] = 1;
  for (i = 2; i <= 1000000; i++) {
    if (composite[i]) continue;
    for (j = 2*i; j <= 1000000; j += i) {
      composite[j] = 1;
    }
  }

  ans[1] = 0;
  for (i = 2; i <= 1000000; i++) {
    ans[i] = ans[i-1] + factors(i);
  }

  while (scanf("%d", &n) == 1) {
    printf("%d\n", ans[n]);
  }

  return 0;
}

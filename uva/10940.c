#include <stdio.h>

#define MAX_N 500000

int ans[MAX_N+1];

void precompute(void)
{
  int n;

  ans[1] = 1;
  for (n = 2; n <= MAX_N; n++) {
    ans[n] = (ans[n-1] == n-1) ? 2 : ans[n-1]+2;
  }
}

int main(void)
{
  int n;

  precompute();
  while (scanf("%d", &n) == 1 && n) {
    printf("%d\n", ans[n]);
  }
  return 0;
}

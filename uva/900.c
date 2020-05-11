#include <stdio.h>

int main(void)
{
  long long ans[51];
  int i, n;

  ans[1] = 1;
  ans[2] = 2;

  for (i = 3; i <= 50; i++) {
    ans[i] = ans[i-1] + ans[i-2];
  }
  
  while (scanf("%d", &n) == 1 && n) {
    printf("%lld\n", ans[n]);
  }
  return 0;
}

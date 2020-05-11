#include <stdio.h>

long long ans[41];

int main(void)
{
  int i, n;

  ans[0] = 1;
  ans[1] = 1;
  ans[2] = 5;
  for (i = 3; i <= 40; i++) {
    ans[i] = ans[i-1] + 4*ans[i-2] + 2*ans[i-3];
  }

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%d", &i);
    printf("%lld\n", ans[i]);
  }

  return 0;
}

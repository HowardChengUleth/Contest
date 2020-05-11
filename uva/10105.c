/* @JUDGE_ID: 1102NT 10105 C "" */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int fact[13];
  int i, n, k, ans;

  fact[0] = 1;
  for (i = 1; i <= 12; i++) {
    fact[i] = fact[i-1] * i;
  }

  while (scanf("%d %d", &n, &k) == 2) {
    ans = fact[n];
    for (i = 0; i < k; i++) {
      scanf("%d", &n);
      ans /= fact[n];
    }
    printf("%d\n", ans);
  }
  return 0;
}

/* @JUDGE_ID: 1102NT 10450 C "" */

#include <stdio.h>

int main(void)
{
  long long F[2][51];
  int n, cases, i;

  F[0][1] = F[1][1] = 1;
  for (n = 2; n <= 50; n++) {
    F[0][n] = F[0][n-1] + F[1][n-1];
    F[1][n] = F[0][n-1];
  }
  
  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    scanf("%d", &n);
    printf("Scenario #%d:\n", i);
    printf("%lld\n\n", F[0][n] + F[1][n]);
  }
  return 0;

}

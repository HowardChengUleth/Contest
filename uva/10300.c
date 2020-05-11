/* @JUDGE_ID: 1102NT 10300 C "" */

#include <stdio.h>

int main(void)
{
  int T;

  scanf("%d", &T);
  while (T-- > 0) {
    int F, S = 0;
    int a, b;
    scanf("%d", &F);
    while (F-- > 0) {
      scanf("%d %*d %d", &a, &b);
      S += a*b;
    }
    printf("%d\n", S);
  }
  return 0;
}

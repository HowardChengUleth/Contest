/* @JUDGE_ID: 1102NT 10812 C "" */

#include <stdio.h>

int main(void)
{
  int n;
  int s, d;
  int a, b;

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%d %d", &s, &d);
    a = (s+d) / 2;
    b = (s-d) / 2;
    if (b >= 0 && (s+d) % 2 == 0) {
      printf("%d %d\n", a, b);
    } else {
      printf("impossible\n");
    }
  }
  return 0;
}

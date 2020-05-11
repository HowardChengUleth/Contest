/* @JUDGE_ID: 1102NT 10055 C "" */

#include <stdio.h>

int main(void)
{
  long long a, b;

  while (scanf("%lld %lld", &a, &b) == 2) {
    if (a < b) {
      printf("%lld\n", b - a);
    } else {
      printf("%lld\n", a - b);
    }
  }
  return 0;
}

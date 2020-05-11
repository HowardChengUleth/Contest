/* @JUDGE_ID: 1102NT 10323 C "" */

#include <stdio.h>

int main(void)
{
  int n;
  long long fact;
  int i;

  while (scanf("%d", &n) == 1) {
    fact = 1;
    for (i = 1; i <= n; i++) {
      fact *= i;
      if (fact > 6227020800LL) {
	break;
      }
    }
    if ((n < 0 && n % 2 == 0) || (n >= 0 && fact < 10000)) {
      printf("Underflow!\n");
    } else if ((n < 0 && n % 2 != 0) || (n >= 0 && i <= n)) {
      printf("Overflow!\n");
    } else {
      printf("%lld\n", fact);
    }
  }
  return 0;
}

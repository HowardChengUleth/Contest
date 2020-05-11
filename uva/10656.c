/* @JUDGE_ID: 1102NT 10656 C "" */

#include <stdio.h>

int main(void)
{
  int N, x, printed;

  while (scanf("%d", &N) == 1 && N > 0) {
    printed = 0;
    while (N-- > 0) {
      scanf("%d", &x);
      if (x > 0) {
	printf("%s%d", (printed) ? " " : "", x);
	printed = 1;
      }
    }
    if (printed) {
      printf("\n");
    } else {
      printf("0\n");
    }
  }
  return 0;
}

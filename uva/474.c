/* @JUDGE_ID: 1102NT 474 C "" */

#include <stdio.h>

double mantissa[1000001];
int exponent[1000001];

int main(void)
{
  int i, n;

  mantissa[1] = 5;
  exponent[1] = -1;
  for (i = 2; i <= 1000000; i++) {
    mantissa[i] = mantissa[i-1] / 2.0;
    exponent[i] = exponent[i-1];
    if (mantissa[i] < 1) {
      mantissa[i] *= 10;
      exponent[i]--;
    }
  }

  while (scanf("%d", &n) == 1) {
    printf("2^-%d = %.3fe%d\n", n, mantissa[n], exponent[n]);
  }
  return 0;

}

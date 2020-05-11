/* @JUDGE_ID: 1102NT 491 C "" */

#include <stdio.h>

/* see http://www.kevingong.com/Polyominoes/Enumeration.html */

long long values[23] = {
  0,
  1,
  1,
  2,
  7,
  18,
  60,
  196,
  704,
  2500,
  9189,
  33896,
  126759,
  476270,
  1802312,
  6849777,
  26152418,
  100203194,
  385221143,
  1485200848,
  5741256764LL,
  22245940545LL,
  86383382827LL
};

int main(void)
{
  int n;
  while (scanf("%d", &n) == 1) {
    printf("%d\n", values[n]);
  }
  return 0;
}

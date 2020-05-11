/* @JUDGE_ID: 1102NT 10469 C "" */

#include <stdio.h>

int main(void)
{
  unsigned long a, b, r;

  while (scanf("%lu %lu", &a, &b) == 2) {
    r = a ^ b;
    printf("%lu\n", r);
  }
  return 0;
}

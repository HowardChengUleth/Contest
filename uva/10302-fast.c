/* @JUDGE_ID: 1102NT 10302 C "" */

/* just figure out the closed form formula */

#include <stdio.h>

int main(void)
{
  long long x;

  while (scanf("%lld", &x) == 1) {
    printf("%lld\n", (x*(x+1)/2)*(x*(x+1))/2);  /* beware of overflow */
  }
  return 0;
}

/* @JUDGE_ID: 1102NT 10633 C "" */

#include <stdio.h>


int main(void)
{
  unsigned long long x;
  unsigned long long lo, hi;
  int first;

  while (scanf("%llu", &x) == 1 && x) {
    hi = 10*x/9;
    if ((10*x-9) % 9 == 0) {
      lo = (10*x-9)/9;
    } else {
      lo = (10*x-9)/9 + 1;
    }
    first = 1;
    while (lo <= hi) {    /* actually, hi - lo <= 1 so there at most 2 */
      if (lo - lo/10 == x) {
	printf("%s%llu", (first) ? "" : " ", lo);
	first = 0;
      }
      lo++;
    }
    printf("\n");
  }
  return 0;
}

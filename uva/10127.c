/* @JUDGE_ID: 1102NT 10127 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void process(int n)
{
  /* we know that m <= n because of pigeonhole principle:
     look at m 1's mod n.  If none of the values of m <= n
     yield a remainder of 0, we get a contradiction that
     n is divisible by 2 or 5. */
  int m = 1, r;

  for (r = 1 % n; r; m++) {
    r = (10*r+1) % n;
  }
  printf("%d\n", m);
}

int main(void)
{
  int n;
  
  while (scanf("%d", &n) == 1) {
    process(n);
  }
   
  return 0;
}

/* @JUDGE_ID: 1102NT 10346 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  int n, k;

  while (scanf("%d %d", &n, &k) == 2) {
    printf("%d\n", ((n-1)/(k-1))*k + 1 + (n-1)%(k-1));
  }
  return 0;

}
